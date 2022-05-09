#ifndef TEMPLATE_DISPATCHER_H
#define TEMPLATE_DISPATCHER_H
namespace messaging {
template<
    typename PreviousDispatcher,
    typename Msg,
    typename Func>
class TemplateDispatcher {
    /*TemplateDispatcher instantiations are friends of each other*/
    template<typename Dispatcher,typename OtherMsg,typename OtherFunc>
    friend class TemplateDispatcher;
public:
    TemplateDispatcher(TemplateDispatcher&& other) : q(other.q), prev(other.prev),
        f(std::move(other.f)), chained(other.chained)
    {
        other.chained = true; //the source shouldn't waiting for
    }

    TemplateDispatcher(queue* q_, PreviousDispatcher* prev_, Func&& f_) :
        q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false)
    {
        prev->chained = true;
    }

    TemplateDispatcher(TemplateDispatcher const&) = delete;
    TemplateDispatcher& operator=(TemplateDispatcher const&) = delete;

    /*additional handlers can be chained*/
    template<typename OtherMsg, typename OtherFunc>
    TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc> handle(OtherFunc&& of)
    {
        return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(
            q, this, std::forward<OtherFunc>(of));
    }

    /** due to any of the handlers might throw an exception,
     * including the dispacher's default handler for close_queue messagers
     * the destructor must once again be declared noexcept(false).
    */
    ~TemplateDispatcher() noexcept(false)
    {
        if (!chained) {
            wait_and_dispatch(); //waiting for a message
        }
    }

private:
    void wait_and_dispatch()
    {
        for (;;) {
            auto msg = q->wait_and_pop();
            if (dispatch(msg)) {
                break; //if you handle the message, break out of the loop
            }
        }
    }

    bool dispatch(std::shared_ptr<message_base> const& msg)
    {
        auto wrapper = dynamic_cast<wrapped_message<Msg>*>(msg.get())
        if (wrapper != nullptr) {
            f(wrapper->contents); // check the message type and call the function
            return true;
        } else {
            return prev->dispatch(msg); // chain to the previous dispatcher
        }
    }

private:
    queue* q;
    PreviousDispatcher* prev;
    Func f;
    bool chained;
};
}
#endif
