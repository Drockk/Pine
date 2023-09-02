#include "Pine.hpp"

#include <format>
#include <iostream>
#include <string>

class Message: public pine::Event
{
public:
    Message(const std::string& t_message) : m_message{ t_message } {

    }

    auto getMessage() -> std::string
    {
        return m_message;
    }

    ~Message() override = default;

private:
    std::string m_message{};
};

class Test
{
public:
    auto init() -> void
    {
        m_eventBus.subscribe(this, &Test::onMessage);
    }

    auto sendMessage(const std::string t_message) -> void
    {
        m_eventBus.append(new Message(t_message));
    }

    auto dispatch() -> void
    {
        m_eventBus.dispatch();
    }

    auto onMessage(Message* t_message) -> void
    {
        std::cout << t_message->getMessage();
        delete t_message;
    }

private:
    pine::EventBus m_eventBus;
};

auto main() -> int
{
    Test test;
    test.init();

    for (auto i{ 0 }; i < 10; ++i) {
        test.sendMessage(std::format("Test: {}\n", i));
    }

    test.dispatch();

    return 0;
}
