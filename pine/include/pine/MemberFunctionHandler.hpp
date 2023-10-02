//
// Created by Bartosz Zielonka on 02.10.2023.
//

#ifndef PINE_MEMBERFUNCTIONHANDLER_HPP
#define PINE_MEMBERFUNCTIONHANDLER_HPP

#include "Event.hpp"

namespace pine
{
    class FunctionHandlerBase
    {
    public:
        void execute(Event* t_event)
        {
            call(t_event);
        }

    private:
        virtual void call(Event* t_event) = 0;
    };

    template<class T, class EventType>
    class MemberFunctionHandler: public FunctionHandlerBase
    {
    public:
        typedef void(T::*MemberFunction)(EventType*);

        MemberFunctionHandler(T* t_instance, MemberFunction t_memberFunction) : m_instance{ t_instance }, m_memberFunction{ t_memberFunction }
        {
        }

        void call(Event* t_event) override
        {
            (m_instance->*m_memberFunction)(static_cast<EventType*>(t_event));
        }

    private:
        T* m_instance;
        MemberFunction m_memberFunction;
    };
}

#endif //PINE_MEMBERFUNCTIONHANDLER_HPP
