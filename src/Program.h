//
// Created by hunde on 3/30/2024.
//

#ifndef PROGRAM_H
#define PROGRAM_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "State.h"

class Program : public State{



    void Update() override;
    void Render() override;

public:
    Program(StateMachine* p_sm, sf::RenderWindow* p_rw);
    ~Program();


};



#endif //PROGRAM_H
