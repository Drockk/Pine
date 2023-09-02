#pragma once
#include "Event.hpp"

namespace pine
{
    class FunctionHandlerBase
    {
    public:
        auto execute(Event* t_event) -> void {
            call(t_event);
        }
    private:
        virtual auto call(Event* t_event) -> void = 0;
    };

    template<class T, class EventType>
    class MemberFunctionHandler: public FunctionHandlerBase
    {
    public:
        typedef void(T::*MemberFunction)(EventType*);

        MemberFunctionHandler(T* t_instance, MemberFunction t_memberFunction) : m_instance{ t_instance }, m_memberFunction{ t_memberFunction }
        {

        }

        auto call(Event* t_event) -> void override
        {
            (m_instance->*m_memberFunction)(static_cast<EventType*>(t_event));
        }

    private:
        T* m_instance;
        MemberFunction m_memberFunction;
    };
}
