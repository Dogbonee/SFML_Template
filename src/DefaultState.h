//
// Created by hunde on 3/30/2024.
//

#ifndef PROGRAM_H
#define PROGRAM_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "State.h"

class DefaultState : public State{


    void Render() override;

public:
    DefaultState(StateMachine* p_sm, sf::RenderWindow* p_rw);
    ~DefaultState() override;

    void Update(float dt) override;
    void Start() override;
    void Exit() override;

};



#endif //PROGRAM_H
