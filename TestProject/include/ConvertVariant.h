#include <variant>
#include <functional>
#include <type_traits>

template<typename T, typename Q>
using is_decayed_same = std::is_same<std::decay_t<T>, Q>;

template<typename T, typename Q>
using if_is_decayed_same = std::enable_if_t<is_decayed_same<T, Q>::value, void*>;

template<typename T, typename Q>
using if_is_not_decayed_same = std::enable_if_t<not is_decayed_same<T, Q>::value, void*>;

// Create a visitor which forwards the call to the visitor it wraps except for a specific type.
// Usefull when you want to perform operations on a variant while knowing one of the possible types
// it contains is not the current value.
template<typename IgnoreType, typename Wrapped>
struct IgnoreTypeVisitor
{
    using result_type = typename std::remove_reference_t<Wrapped>::result_type;
    Wrapped d_wrapped;

    template<typename T, if_is_not_decayed_same<T, IgnoreType> = nullptr>
    result_type operator()(T&& value)
    {
        return std::invoke(std::forward<Wrapped>(d_wrapped), std::forward<T>(value));
    }
};

template<typename IgnoreType, typename Wrapped>
IgnoreTypeVisitor<IgnoreType, Wrapped> make_ignoretype(Wrapped&& wrapped)
{
    return IgnoreTypeVisitor<IgnoreType, Wrapped>{std::forward<Wrapped>(wrapped)};
}

// Construct an object with the current value of a variant
template<typename ConstructedType>
struct ConstructVisitor
{
    // this is required because boost (possible implementation of variant) requires it from
    // visitors.
    using result_type = ConstructedType;

    template<typename T>
    ConstructedType operator()(T&& value)
    {
        return ConstructedType{std::forward<T>(value)};
    }
};

template <class... Args>
struct variant_cast_impl
{
    std::variant<Args...> v;

    template <class... ToArgs>
    operator std::variant<ToArgs...> ()
    {
        return std::visit([](auto&& arg) -> std::variant<ToArgs...> { return arg; }, v);
    }
};

template <class... Args>
auto variant_cast(std::variant<Args...>& v) -> variant_cast_impl<Args...>
{
    return {v};
}
