//
// Created by hunde on 3/30/2024.
//

#ifndef PROGRAM_H
#define PROGRAM_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Program {

    sf::RenderWindow m_window;

    void Update();
    void HandleEvents();
    void HandleKeyboardInput(sf::Keyboard::Key key);
    void Render();

public:
    Program();
    ~Program();
    void Run();


};



#endif //PROGRAM_H
