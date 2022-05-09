#ifndef SIMPLE_CALLBACKLIST_H
#define SIMPLE_CALLBACKLIST_H

#include <vector>
#include <iostream>
#include <functional>
#include <type_traits>

namespace detail {
template<typename T, typename F>
using if_is_constructile = std::enable_if_t<std::is_constructible<T, F>::value, void*>;
}

template<typename Callable>
struct SimpleCallbackList {
public:
    SimpleCallbackList() = default;

    using CallbackFunctionType = Callable;

    /**
    * @brief calls every connected callback function with the provided arguements
    * @note if during this call a callback function in this list removes other callbacks within the same list, it is undefined if the
    *  removed callbacks will also be called.
    * @param args arguements to call each callback function with
    */
    template<typename... Args>
    void operator()(Args... args)
    {
        for (auto& func : m_cbFuncs) {

            std::invoke(func, args...);
        }
    }

    /// @brief Connects a function which will be called every time this list is called, until the
    /// returned smart ptr dies.
    /// @param f the functor you wish to called whenever this callback list is called.
    /// @return unique_ptr to newly connected callback, should be added to a callback holder with the same desired
    /// lifespan as the connected function. The only way to remove a connected functor is through the destruction
    /// of this returned unique_ptr
    template<typename F, detail::if_is_constructile<CallbackFunctionType, F> = nullptr>
    void Emplace(F&& f)
    {
        m_cbFuncs.emplace_back(std::forward<F>(f));
    }

private:
    std::vector<CallbackFunctionType> m_cbFuncs;
};


//=====================================================================================
namespace annot {
int funcA(int a)
{
    std::cout << "input parameter is " << a << std::endl;
    return a;
}

struct TestB {
public:
    int funcB(int a)
    {
        std::cout << "TestB member function: input parameter is " << a << std::endl;
        return a;
    }
};
}

void Test_SimpleCallbackList()
{
    std::cout << "Test SimpleCallbackList" << std::endl;

    using FuncType = std::function<int(int)>;
    SimpleCallbackList<FuncType> sl;

    // sl.Emplace(funcA);

    annot::TestB b{};
    FuncType f = [&b](int a) {return b.funcB(a);};
    sl.Emplace(f);

    sl(4);
}


#endif //CALLBACKLIST_H
