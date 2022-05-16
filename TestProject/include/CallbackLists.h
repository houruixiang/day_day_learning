#ifndef CALLBACKLIST_H
#define CALLBACKLIST_H

#include <vector>
#include <functional>

//todo account for callbacks disconnecting other callbacks without having traversal of callbacks being called invalidated
struct ICallbackList {
public:
    ICallbackList() = default;

    virtual ~ICallbackList() { DisconnectAll(); }

    virtual bool Empty() const { return m_callbacks.empty(); }

    struct ICallback {
    public:
        ICallback() = default;

        ICallback(const ICallback&) = delete;

        ICallback(ICallback&& rhs) : m_listConnectedTo(rhs.m_listConnectedTo),
            m_connectedFunctionIndex(rhs.m_connectedFunctionIndex) {
            rhs.m_listConnectedTo = nullptr;
            m_listConnectedTo->m_callbacks[m_connectedFunctionIndex] = this;
        }

        virtual ~ICallback() {
            if (m_listConnectedTo != nullptr) {
                m_listConnectedTo->Disconnect(m_connectedFunctionIndex);
            }
        }

        explicit ICallback(ICallbackList* listConnectingTo, std::size_t index)
                : m_listConnectedTo(listConnectingTo), m_connectedFunctionIndex(index) {
            listConnectingTo->m_callbacks.emplace_back(this);
        }

    private:
        ICallbackList* m_listConnectedTo {nullptr};
        std::size_t m_connectedFunctionIndex;

        friend struct ICallbackList;
    };

protected:
    virtual void Disconnect(std::size_t index)
    {
        m_callbacks[index]->m_listConnectedTo = nullptr;
        m_callbacks[index] = std::move(m_callbacks.back());
        m_callbacks[index]->m_connectedFunctionIndex = index;
        m_callbacks.pop_back();
    }

    virtual void DisconnectAll()
    {
        for (auto* cb : m_callbacks) {
            cb->m_listConnectedTo = nullptr;
        }
        m_callbacks.clear();
    };

    std::vector<ICallback*> m_callbacks;
};

using ICallback=ICallbackList::ICallback;

// CallbackList
template<typename Signature>
struct CallbackList;

template<typename Callable>
struct CallbackList : public ICallbackList {
public:
    CallbackList() = default;

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
    template<typename F>
    [[nodiscard]]  std::enable_if_t<std::is_constructible<CallbackFunctionType, F>::value,
            ICallback> Connect(F&& f) {
        m_cbFuncs.emplace_back(std::forward<F>(f));
        return ICallback{this, m_cbFuncs.size() - 1};
    }

    /// @brief Connects a member function of the provided object instance to be called every time
    /// this callback list is called, as long as the returned smart ptr hasn't deleted itself.
    /// @param obj the object that the member function will be called on
    /// @param memberFunc the member function belonging to the provided object
    /// @return unique_ptr to newly connected callback, should be added to a callback holder.
    template<typename T, typename ConvertibleR, typename... ConvertibleArgs>
    [[nodiscard]] ICallback Connect(T* obj, ConvertibleR(T::*memberFunc)(ConvertibleArgs...)) {
        return Connect([=](ConvertibleArgs... args) -> ConvertibleR { return (obj->*memberFunc)(args...); });
    };

protected:
    std::vector<CallbackFunctionType> m_cbFuncs;

    //when a callback removes a different callback gaurentee said callback will be called before it is removes
    void Disconnect(std::size_t index) override
    {
        ICallbackList::Disconnect(index);
        m_cbFuncs[index] = std::move(m_cbFuncs.back());
        m_cbFuncs.pop_back();
    }

    void DisconnectAll() override
    {
        ICallbackList::DisconnectAll();
        m_cbFuncs.clear();
    }
};

template<typename R, typename... Args>
struct CallbackList<R(Args...)> : public ICallbackList {
public:
    CallbackList() = default;

    using CallbackFunctionType = std::function<R(Args...)>;

    /**
    * @brief calls every connected callback function with the provided arguements
    * @note if during this call a callback function in this list removes other callbacks within the same list, it is undefined if the
    *  removed callbacks will also be called.
    * @param args arguements to call each callback function with
    */
    virtual void operator()(Args... args)
    {
        Apply(args...);
    }

    /// @brief Connects a function which will be called every time this list is called, until the
    /// returned smart ptr dies.
    /// @param f the functor you wish to called whenever this callback list is called.
    /// @return unique_ptr to newly connected callback, should be added to a callback holder with the same desired
    /// lifespan as the connected function. The only way to remove a connected functor is through the destruction
    /// of this returned unique_ptr
    template<typename F>
    [[nodiscard]]  std::enable_if_t<std::is_constructible<CallbackFunctionType, F>::value,
            ICallback> Connect(F&& f) {
        m_cbFuncs.emplace_back(std::forward<F>(f));
        return ICallback{this, m_cbFuncs.size() - 1};
    }

    /// @brief Connects a member function of the provided object instance to be called every time
    /// this callback list is called, as long as the returned smart ptr hasn't deleted itself.
    /// @param obj the object that the member function will be called on
    /// @param memberFunc the member function belonging to the provided object
    /// @return unique_ptr to newly connected callback, should be added to a callback holder.
    template<typename T, typename ConvertibleR, typename... ConvertibleArgs>
    [[nodiscard]] ICallback Connect(T* obj, ConvertibleR(T::*memberFunc)(ConvertibleArgs...)) {
        return Connect([=](ConvertibleArgs... args) -> ConvertibleR { return (obj->*memberFunc)(args...); });
    };

protected:
    std::vector<CallbackFunctionType> m_cbFuncs;

    //when a callback removes a different callback gaurentee said callback will be called before it is removes
    void Disconnect(std::size_t index) override
    {
        ICallbackList::Disconnect(index);
        m_cbFuncs[index] = std::move(m_cbFuncs.back());
        m_cbFuncs.pop_back();
    }

    void DisconnectAll() override
    {
        ICallbackList::DisconnectAll();
        m_cbFuncs.clear();
    }

    void Apply(Args... args)
    {
        for (auto& func : m_cbFuncs) {
            func(args...);
        }
    }
};

struct CallbackHolder : public std::vector<ICallback> {
public:
    auto emplace(ICallback&& cb) -> decltype(emplace_back(std::move(cb)))
    {
        return emplace_back(std::move(cb));
    }
};



//=====================================================================================
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

void Test_CallbackList()
{
    std::cout << std::endl << "---Test CallbackList---" << std::endl;

    using Func = std::function<int(int)>;
    CallbackList<Func> l;
    CallbackHolder holder;
    // CallbackList<int(int)> l;
    holder.emplace(l.Connect(funcA));

    TestB b{};
    auto f = [&b](int a) {return b.funcB(a);};
    holder.emplace(l.Connect(f));

    holder.emplace(l.Connect(&b, &TestB::funcB));

    l(4);
}


#endif //CALLBACKLIST_H
