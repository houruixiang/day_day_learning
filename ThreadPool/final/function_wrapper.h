#include <deque>
#include <future>
#include <memory>
#include <functional>
#include <iostream>

class function_wrapper
{
    struct impl_base {
        virtual void call()=0;
        virtual ~impl_base() {}
    };
    std::unique_ptr<impl_base> impl;
    template<typename F>
    struct impl_type: impl_base
    {
        F f;
        impl_type(F&& f_): f(std::move(f_)) {}
        void call() { f(); }
    };
public:
    template<typename F>
    function_wrapper(F&& f) : impl(new impl_type<F>(std::move(f)))
    {}

    function_wrapper(): impl(nullptr) {}

    function_wrapper(function_wrapper&& other) : impl(std::move(other.impl))
    {}

    function_wrapper& operator=(function_wrapper&& other)
    {
        impl = std::move(other.impl);
        return *this;
    }

    void call() 
    {
        if (impl != nullptr) {
            impl->call();
        }
    }

    void operator()()
    {
        if (impl != nullptr) {
            impl->call();
        }     
    }

    function_wrapper(const function_wrapper&)=delete;
    function_wrapper(function_wrapper&)=delete;
    function_wrapper& operator=(const function_wrapper&)=delete;
};

// class thread_pool
// {
// public:
//     std::deque<function_wrapper> work_queue;

//     template<typename FunctionType>
//     std::future<typename std::result_of<FunctionType()>::type>
//     submit(FunctionType f)
//     {
//         typedef typename std::result_of<FunctionType()>::type result_type;
        
//         std::packaged_task<result_type()> task(std::move(f));
//         std::future<result_type> res(task.get_future());
//         work_queue.push_back(std::move(task));
//         return res;
//     }

//     void run_pending_task()
//     {
//         function_wrapper task;
//         if(work_queue.try_pop(task))
//         {
//             task();
//         }
//         else
//         {
//             std::this_thread::yield();
//         }
//     }
//     // rest as before
// };
