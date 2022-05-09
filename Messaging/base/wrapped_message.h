#ifndef WARPPED_MESSAGE_H
#define WARPPED_MESSAGE_H

namespace messaging {
struct message_base {
    virtual ~message_base() {}
};

/*
    each message type has a specialization
*/
template<typename Msg>
struct wrapped_message: public message_base {
    Msg contents;
    explicit wrapped_message(Msg const& contents_): contents(contents_) {}
};
}
#endif