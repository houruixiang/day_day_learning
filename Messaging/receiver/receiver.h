#ifndef RECEVIER_H
#define RECEVIER_H

#include "base/queue.h"
#include "sender/sender.h"
#include "dispatcher/dispatcher.h"

namespace messaging {
class receiver {
public:
    operator sender()
    {
        return sender(&q); //allow implcit conversion to a sender that references the queue
    }

    dispatcher wait()
    {
        return dispatcher(&q); //wait for a queue creates a dispathcer
    }

private:
    queue q; //a receiver owns the queue
};
}
#endif
