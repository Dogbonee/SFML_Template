//
// Created by hunde on 3/30/2024.
//

#include "StateMachine.h"

#include "DefaultState.h"


StateMachine::StateMachine() : m_window(sf::VideoMode(800, 600), "Default Name")
{
    m_states.emplace_back(std::make_shared<DefaultState>(this, &m_window));
}

StateMachine::~StateMachine() = default;

void StateMachine::UpdateCurrentState()
{
    p_currentState->Update(m_dt);
}

void StateMachine::ChangeState(STATES state)
{
    try
    {
        auto newState = m_states.at(state);
        if(p_currentState)
        {
            p_currentState->Exit();
        }
        p_currentState = newState;
        p_currentState->Start();
    }catch (std::exception& e)
    {
        std::cout << "State does not exist\n";
        exit(1);
    }
}

void StateMachine::StartStateMachine()
{
    if(p_currentState == nullptr)
    {
        std::cout << "A state must be set before starting the state machine\n";
        exit(1);
    }
    while(m_window.isOpen())
    {
        m_dt = m_clock.restart().asSeconds();
        UpdateCurrentState();
    }
}


