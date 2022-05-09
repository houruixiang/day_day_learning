#ifndef SENDER_H
#define SENDER_H

#include "base/queue.h"

namespace messaging {
class sender {
public:
    sender(): q(nullptr) {} //default-constructed sender has no queue
    explicit sender(queue *q_): q(q_) {} //allow construction from pointer to queue

    template<typename Message>
    void send(Message const& msg)
    {
        if (q) {
            q->push(msg); //sending pushes message on the queue
        }
    }

private:
    queue *q; //sender ifi a wrapper around the queue potinter
};
}
#endif
