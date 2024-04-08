//
// Created by hunde on 3/30/2024.
//

#include "Program.h"

Program::Program(StateMachine* p_sm, sf::RenderWindow* p_rw) : State(p_sm, p_rw)
{
}

Program::~Program() = default;

void Program::Update()
{
    HandleEvents();
    Render();
}


void Program::Render()
{
    p_window->clear();
    p_window->display();
}
