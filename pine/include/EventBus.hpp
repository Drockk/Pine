#pragma once
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
        auto publish(EventType* t_event) -> void
        {
            auto* handlers = m_subscribers.at(typeid(EventType));

            if (handlers == nullptr) {
                return;
            }

            for (auto& handler : *handlers) {
                if (handler != nullptr) {
                    handler->execute(t_event);
                }
            }
        }

        template<typename T, class EventType>
        auto subscribe(T* instance, void (T::* memberFunction)(EventType*)) {
            HandlerList* handlers = m_subscribers[typeid(EventType)];

            if (handlers == nullptr) {
                handlers = new HandlerList();
                m_subscribers[typeid(EventType)] = handlers;
            }

            handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
        }

        template<typename EventType>
        auto append(EventType* t_event) -> void
        {
            m_QueuedEvents.emplace(typeid(EventType), static_cast<Event*>(t_event));
        }

        auto dispatch() -> void
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
