#ifndef CALLBACK_DELEGATE_H
#define CALLBACK_DELEGATE_H

#include <vector>
#include <iostream>
#include <functional>
#include <type_traits>

namespace detail {
/**
 * non specialized template declaration for Delegate
 */
template <typename T>
struct Delegate;

/**
 * specialization for member functions
 *
 * @tparam T            class-type of the object who's member function to call
 * @tparam R            return type of the function that gets captured
 * @tparam params       variadic template list for possible arguments
 *                      of the captured function
 */
template <typename T, typename R, typename... Params>
struct Delegate<R (T::*)(Params...)> {
public:
    typedef R (T::*FuncType)(Params...);

    Delegate(FuncType func, T& callee) : m_callee(callee), m_func(func) {}

    R operator()(Params... args) const
    {
        return (m_callee.*m_func)(args...);
    }

    bool operator==(const Delegate& other) const
    {
        return (&m_callee == &other.m_callee) && (m_func == other.m_func);
    }

    bool operator!= (const Delegate& other) const
    {
        return !((*this) == other);
    }

private:
    T& m_callee;
    FuncType m_func;
};

/**
 * specialization for const member functions
 */
template <typename T, typename R, typename... Params>
struct Delegate<R (T::*)(Params...) const>
{
public:
    typedef R (T::*FuncType)(Params...) const;

    Delegate(FuncType func, const T& callee) : m_callee(callee), m_func(func) {}

    R operator()(Params... args) const
    {
        return (m_callee.*m_func)(args...);
    }

    bool operator==(const Delegate& other) const
    {
        return (&m_callee == &other.m_callee) && (m_func == other.m_func);
    }

    bool operator!= (const Delegate& other) const
    {
        return !(*this == other);
    }

private:
    const T& m_callee;
    FuncType m_func;
};

/**
 * specialization for free functions
 *
 * \tparam R            return type of the function that gets captured
 * \tparam params       variadic template list for possible arguments
 *                      of the captured function
 */
template <typename R, typename... Params>
struct Delegate<R (*)(Params...)>
{
public:
    typedef R (*FuncType)(Params...);

    Delegate(FuncType func) : m_func(func) {}

    R operator()(Params... args) const
    {
        return (*m_func)(args...);
    }

    bool operator==(const Delegate& other) const
    {
        return m_func == other.m_func;
    }
    bool operator!= (const Delegate& other) const
    {
        return !((*this) == other);
    }

private:
    FuncType m_func;
};
} //namespace detail

/**
 * function to deduce template parameters from call-context
 */
template <typename F, typename T>
detail::Delegate<F> MakeDelegate(F func, T& obj)
{
    return detail::Delegate<F>(func, obj);
}

template <typename F>
detail::Delegate<F> MakeDelegate(F func)
{
    return detail::Delegate<F>(func);
}


//-----------------------------------------------------------------------------

class listener {
public:
    void msgReceived(int len)
    {
        std::cout << "msgReceived len: " << len << std::endl;
    }
    void msgReceivedC(int len) const
    {
        std::cout << "msgReceived const len: " << len << std::endl;
    }
};

// using RegistryDelegate = detail::Delegate<void (*)(int)>;
typedef  detail::Delegate<void (*)(int)> RegistryDelegate;
class Service {
public:

    void RegisterDelegate(RegistryDelegate&& d)
    {
        m_delegate = std::move(&d);
    }

    void NotifyDelegate(int a)
    {
        (*m_delegate)(a);
    }

private:
    RegistryDelegate* m_delegate {nullptr};
};

// MakeDelegate返回的类型含有Class信息，还是没有办法统一存储
void Test_Delegate()
{
    std::cout << std::endl << "---Test Delegate---" << std::endl;

    listener l;
    auto d = MakeDelegate(&listener::msgReceived, l);
    // ...
    d(42);

    listener cl;
    auto cd = MakeDelegate(&listener::msgReceivedC, cl);
    cd(38);

    // Service s;
    // s.RegisterDelegate(d);

}

#endif