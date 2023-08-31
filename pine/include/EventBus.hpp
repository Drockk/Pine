#pragma once
#include "MemberFunctionHandler.hpp"

#include <map>
#include <list>
#include <typeindex>

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
            auto* handlers = m_subscribers.at(typeid(EventType));

            if (handlers == nullptr) {
                handlers = new HandlerList();
                m_subscribers[typeid(EventType)] = handlers;
            }

            handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
        }

    private:
        std::map<std::type_index, HandlerList*> m_subscribers;
    };
}
