//
// Created by hunde on 3/30/2024.
//

#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <vector>
#include "State.h"

//When you want to create a new state, make sure you append this enum
enum STATES
{
    DEFAULT_STATE = 0
};

class StateMachine {

    sf::RenderWindow m_window;

    std::vector<State*> m_states;
    State* p_currentState = nullptr;


    void UpdateCurrentState();


public:
    StateMachine();
    ~StateMachine();
    void ChangeState(STATES state);
    void StartStateMachine();
};



#endif //STATEMACHINE_H
