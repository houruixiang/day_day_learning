#ifndef DISPATHCER_H
#define DISPATHCER_H

#include <memory>
#include "base/queue.h"
#include "TemplateDispatcher.h"

namespace messaging {
class close_queue {}; //the message for closing the queue

class dispatcher {
template<
    typename Dispatcher,
    typename Msg,
    typename Func>
friend class TemplateDispatcher; //allow TemplateDispatcher instances to access the internals

public:
    explicit dispatcher(queue* q_) : q(q_),chained(false) {}
    dispatcher(const dispatcher&) = delete; //can't be copied
    dispatcher& operator=(const dispatcher&) = delete;

    dispatcher(dispatcher&& other) : q(other.q), chained(other.chained) // can be moved
    {
        other.chained = true; //the source shouldn't wait for messages
    }

    /*
        the meassage type is not deducible, so you must specify which message type to handle
        and pass in a function or callable object to handle it
    */
    template<typename Message,typename Func>
    TemplateDispatcher<dispatcher, Message, Func> handle(Func&& f)
    {
        return TemplateDispatcher<dispatcher, Message, Func>(
            q, this, std::forward<Func>(f)); //handle a specific type of message with a TemplateDispatcher
    }

    ~dispatcher() noexcept(false) //the destructor might throw exceptions
    {
        if (!chained) {
            wait_and_dispatch(); //the word is done
        }
    }

private:
    void wait_and_dispatch()
    {
        while (true) { //loop
            auto msg = q->wait_and_pop(); //waiting for
            dispatch(msg); // dispatching messages
        }
    }

    bool dispatch(const std::shared_ptr<message_base>& msg)
    {
        if (dynamic_cast<wrapped_message<close_queue>*>(msg.get())) {
            throw close_queue(); // check for a close_queue message and throws
        }
        return false;
    }

private:
    queue* q;
    bool chained;
};
}
#endif
