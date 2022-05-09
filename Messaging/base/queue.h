#ifndef QUEUE_H
#define QUEUE_H

#include <mutex>
#include <queue>
#include <memory>
#include <condition_variable>

#include "wrapped_message.h"

namespace messaging {
class queue {
public:
    template<typename T>
    void push(T const& msg)
    {
        std::lock_guard<std::mutex> lk(m);
        q.push(std::make_shared<wrapped_message<T> >(msg)); //wrap posted message and store pointer

        c.notify_all();
    }

    std::shared_ptr<message_base> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(m);
        c.wait(lk, [&] { return !q.empty(); }); //block until queue isn't empty

        auto res = q.front();
        q.pop();
        return res;
    }

private:
    std::mutex m;
    std::condition_variable c;
    std::queue<std::shared_ptr<message_base> > q; //internal queue stores pointer to message_base
};
}
#endif
