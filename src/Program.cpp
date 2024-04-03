//
// Created by hunde on 3/30/2024.
//

#include "Program.h"



Program::Program() : SCREEN_RES{sf::VideoMode::getDesktopMode()}, m_window(SCREEN_RES, "Game of Life"), m_dt(0), m_tickLength(0.1),
                     m_cameraSpeed(500), m_zoomSpeed(50), m_startButton(sf::Vector2f(300,150), "Start")
{
    m_mode = Mode::Setup;
    m_pods = new PodCollection();

    //Create starting template (glider)
    m_pods->TogglePod(sf::Vector2i(30, 15));
    m_pods->TogglePod(sf::Vector2i(31, 16));
    m_pods->TogglePod(sf::Vector2i(32, 16));
    m_pods->TogglePod(sf::Vector2i(31, 17));
    m_pods->TogglePod(sf::Vector2i(30, 17));

    //Init camera
    m_camera.reset(sf::FloatRect(0,0, SCREEN_RES.width, SCREEN_RES.height));

    //Init button
    m_startButton.setColor(sf::Color::Green);
    m_startButton.callback = ([this]{ToggleMode();});
}

Program::~Program()
{
    delete m_pods;
}

void Program::Update()
{
    m_dt = m_clock.restart().asSeconds();
    HandleEvents();
    //Ideally, we would create a state machine with setup and running states and call
    //update functions according to the state, but this will do for a program of this size.
    if(m_mode == Mode::Running)
    {
        //If no pods exist, set the mode to Setup
        if(m_pods->CollectionSize() == 0)
        {
            ToggleMode();
        }else
        {
            //Otherwise run simulation
            HandleTicks();
        }
    }
    HandleCamera();
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
            //Leaving HandleKeyboardInput in case more keybinds are added later
            case sf::Event::KeyPressed:
                HandleKeyboardInput(event.key.code);
                break;
            //Update buttons only when mouse moves
            case sf::Event::MouseMoved:
                m_startButton.ButtonUpdate(static_cast<sf::Vector2i>(m_window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y))));
                break;
            //Poll buttons and set pod at mousepos if in setup mode
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(m_mode == Mode::Setup)
                    {
                        SetPod(static_cast<sf::Vector2i>(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))));
                    }
                    m_startButton.Activate();
                }
            default: break;
        }
    }
}

void Program::HandleKeyboardInput(sf::Keyboard::Key key)
{
    //Seems useless to have this in a function, but it allows for expansion
    switch(key)
    {
        case sf::Keyboard::Escape:
            m_window.close();
            break;
        default:
            break;
    }
}

void Program::Render()
{
    m_window.clear();
    m_window.setView(m_camera);
    //Maybe don't render if in run mode, but it doesn't really matter either way
    RenderSetupLines(m_window);
    m_window.draw(*m_pods);
    m_window.draw(m_startButton);
    m_window.display();
}

void Program::HandleTicks()
{
    //standard tick function
    static float currentTick = m_tickLength;
    currentTick -= m_dt;
    if(currentTick <= 0)
    {
        m_pods->CalculateNextTurn();
        currentTick = m_tickLength;
    }
}

void Program::HandleCamera()
{
    //Camera zoom is calculated based on the current frame and is change in zoom,
    //while totalZoom is the overall scale of the camera.
    float cameraZoom;
    static float totalZoom = 1;
    m_camera.move((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) * m_cameraSpeed * m_dt,0);
    m_camera.move(0,(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) * m_cameraSpeed * m_dt);
    cameraZoom = 1 -(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) * m_dt) + (sf::Keyboard::isKeyPressed(sf::Keyboard::X) * m_dt);
    totalZoom *= cameraZoom;
    m_camera.zoom(cameraZoom);
    //Need to factor zoom into button transforms to make it appear unaffected by the zoom
    m_startButton.setPosition(m_camera.getCenter() + sf::Vector2f(0, SCREEN_RES.height/4) * totalZoom);
    m_startButton.setScale(sf::Vector2f(totalZoom, totalZoom));

}

void Program::RenderSetupLines(sf::RenderWindow& window)
{
    //TODO: draw lines based on camera location
    //Draw a static grid. Player can technically move the camera outside the grid and zoom out enough
    //to see the end of the grid, which should be fixed. Zoom should be clamped, and camera should either
    //have collision with the border or lines should be dynamically drawn based on camera position.
    for(int i = -PodCollection::PodSize * 333; i < PodCollection::PodSize * 333; i += PodCollection::PodSize)
    {

            sf::Vertex linex[] = {
                sf::Vertex(sf::Vector2f(i, -10000)),
                sf::Vertex(sf::Vector2f(i, 10000))
            };
            sf::Vertex liney[] = {
                sf::Vertex(sf::Vector2f(-10000, i)),
                sf::Vertex(sf::Vector2f(10000, i))
            };
        window.draw(linex, 2, sf::Lines);
        window.draw(liney, 2, sf::Lines);
    }
}

void Program::ToggleMode()
{
    //Toggle mode and button color/text
    m_mode = static_cast<Mode>(static_cast<int>(m_mode) ^ 1);
    m_startButton.setColor(m_mode == Mode::Setup ? sf::Color::Green : sf::Color::Red);
    m_startButton.setButtonText(m_mode == Mode::Setup ? "Start" : "Stop");
}

void Program::SetPod(sf::Vector2i mousePos)
{
    //Convert mousepos to tile coords and call TogglePod
    m_pods->TogglePod(sf::Vector2i(mousePos.x/PodCollection::PodSize, mousePos.y/PodCollection::PodSize));
}

void Program::Run()
{
    while(m_window.isOpen())
    {
        Update();
    }
}

