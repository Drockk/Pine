//
// Created by Bartosz Zielonka on 02.10.2023.
//

#ifndef PINE_EVENTBUS_HPP
#define PINE_EVENTBUS_HPP

#include "MemberFunctionHandler.hpp"

#include <stdexcept>
#include <map>
#include <list>
#include <typeindex>
#include <queue>

namespace pine
{
    typedef std::list<FunctionHandlerBase*> HandlerList;

    class EventBus
    {
    public:
        template<typename EventType>
        void publish(EventType* t_event)
        {
            auto* handlers = m_subscribers.at(typeid(EventType));

            if (handlers == nullptr) {
                return;
            }

            for (auto& handler: *handlers) {
                if (handler != nullptr) {
                    handler->execute(t_event);
                }
            }
        }

        template<typename T, class EventType>
        void subscribe(T* t_instance, void (T::* t_memberFunction)(EventType*))
        {
            auto* handlers = m_subscribers[typeid(EventType)];

            if (handlers == nullptr) {
                handlers = new HandlerList();
                m_subscribers[typeid(EventType)] = handlers;
            }

            handlers->push_back(new MemberFunctionHandler<T, EventType>(t_instance, t_memberFunction));
        }

        template<typename EventType>
        void append(EventType* t_event)
        {
            m_QueuedEvents.emplace(typeid(EventType), static_cast<Event*>(t_event));
        }

        void dispatch()
        {
            if (m_QueuedEvents.empty()) {
                return;
            }

            while (!m_QueuedEvents.empty()) {
                auto [typeId, event] = m_QueuedEvents.front();
                auto* handlers = m_subscribers.at(typeId);

                if (handlers == nullptr) {
                    return;
                }

                for (auto& handler : *handlers) {
                    if (handler != nullptr) {
                        handler->execute(event);
                    }
                }

                m_QueuedEvents.pop();
            }
        }

    private:
        std::map<std::type_index, HandlerList*> m_subscribers;
        std::queue<std::pair<std::type_index, Event*>> m_QueuedEvents;
    };
}

#endif //PINE_EVENTBUS_HPP
