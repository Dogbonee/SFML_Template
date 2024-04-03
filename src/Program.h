//
// Created by hunde on 3/30/2024.
//

#ifndef PROGRAM_H
#define PROGRAM_H
#include <SFML/Graphics.hpp>
#include "PodCollection.h"
#include "Button.h"
enum class Mode {
    Setup,
    Running
};


class Program {

    const sf::VideoMode SCREEN_RES;

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    float m_dt;
    const float m_tickLength;
    sf::View m_camera;
    float m_cameraSpeed;
    float m_zoomSpeed;

    Button m_startButton;

    Mode m_mode;

    void Update();
    void HandleEvents();
    void HandleKeyboardInput(sf::Keyboard::Key key);
    void Render();
    void HandleTicks();
    void HandleCamera();
    void RenderSetupLines(sf::RenderWindow& window);

    PodGroup m_startingPods;

    PodCollection* m_pods;

    void ToggleMode();
    void SetPod(sf::Vector2i mousePos);

public:
    Program();
    ~Program();
    void Run();



};



#endif //PROGRAM_H
