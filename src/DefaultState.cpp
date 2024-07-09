//
// Created by hunde on 3/30/2024.
//

#include "DefaultState.h"

DefaultState::DefaultState(StateMachine* p_sm, sf::RenderWindow* p_rw) : State(p_sm, p_rw)
{
}

DefaultState::~DefaultState() = default;

void DefaultState::Update(float dt)
{
    HandleEvents();
}


void DefaultState::Render()
{
    p_window->clear();
    p_window->display();
}

void DefaultState::Start()
{
}

void DefaultState::Exit()
{
}
