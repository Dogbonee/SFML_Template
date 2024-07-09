//
// Created by hunde on 3/30/2024.
//

#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>

class StateMachine;



class State {


protected:

    StateMachine* p_stateMachine;
    sf::RenderWindow* p_window;


    virtual void HandleEvents();
    virtual void HandleKeyboardInput(sf::Keyboard::Key key);
    virtual void Render() = 0;


public:

    State(StateMachine* p_sm, sf::RenderWindow* p_rw);
    virtual ~State() = default;

    virtual void Update(float dt) = 0;
    virtual void Start() = 0;
    virtual void Exit() = 0;
};



#endif //STATE_H
