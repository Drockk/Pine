//
// Created by Bartosz Zielonka 02.10.2023.
//

#include <pine/Pine.hpp>

#include <format>
#include <iostream>
#include <string>

class Message: public pine::Event
{
public:
    explicit Message(std::string_view t_message): m_message{ t_message }
    {

    }

    ~Message() override = default;

    std::string getMessage()
    {
        return m_message;
    }

private:
    std::string m_message{};
};

class Test
{
public:
    void init()
    {
        m_eventBus.subscribe(this, &Test::onMessage);
    }

    void sendMessage(std::string_view t_message)
    {
        m_eventBus.append(new Message(t_message));
    }

    void dispatch()
    {
        m_eventBus.dispatch();
    }

    void onMessage(Message* t_message)
    {
        std::cout << t_message->getMessage();
        delete t_message;
    }

private:
    pine::EventBus m_eventBus;
};

int main()
{
    Test test;
    test.init();

    for (auto i{ 0 }; i < 10; ++i) {
        test.sendMessage(std::format("Test: {}\n", i));
    }

    test.dispatch();

    return 0;
}
