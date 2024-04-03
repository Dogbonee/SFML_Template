//
// Created by hunde on 3/30/2024.
//

#include "Program.h"

Program::Program() : m_window(sf::VideoMode(800, 600), "Default Name")
{
}

Program::~Program() = default;

void Program::Update()
{
    HandleEvents();
    Render();
}

void Program::HandleEvents()
{
    for(sf::Event event{}; m_window.pollEvent(event);)
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
                HandleKeyboardInput(event.key.code);
                break;

        }
    }
}

void Program::HandleKeyboardInput(sf::Keyboard::Key key)
{
    switch(key)
    {
        default:
            std::cout << "Key pressed: " << key << '\n';
    }
}

void Program::Render()
{
    m_window.clear();
    m_window.display();
}

void Program::Run()
{
    while(m_window.isOpen())
    {
        Update();
    }
}
