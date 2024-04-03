//
// Created by 24crickenbach on 3/26/2024.
//

#include "Button.h"

Button::Button(sf::Vector2f size, sf::String text) : callback(nullptr)
{

    m_buttonFont.loadFromFile("../Pixeboy.ttf");
    m_buttonShape.setSize(size);
    m_buttonShape.setFillColor(sf::Color::Black);
    m_buttonShape.setOutlineColor(sf::Color::White);
    m_buttonShape.setOutlineThickness(3);
    m_buttonShape.setOrigin(size.x/2, size.y/2);
    m_buttonText.setFont(m_buttonFont);
    m_buttonText.setFillColor(sf::Color::White);
    m_buttonText.setCharacterSize(size.x/7);
    setButtonText(text);

}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_buttonShape);
    target.draw(m_buttonText);
}

void Button::setColor(sf::Color color)
{
    m_buttonShape.setOutlineColor(color);
    m_buttonColor = color;
}

void Button::setPosition(const sf::Vector2f &position)
{
    m_buttonShape.setPosition(position);
    m_buttonText.setPosition(position);
}

void Button::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x,y));
}

const sf::Vector2f & Button::getPosition() const
{
    return m_buttonShape.getPosition();
}

void Button::setScale(const sf::Vector2f &scale)
{
    m_buttonShape.setScale(scale);
    m_buttonText.setScale(scale);
}

void Button::setButtonText(sf::String string)
{
    m_buttonText.setString(string);
    sf::FloatRect textRect = m_buttonText.getLocalBounds();
    sf::Vector2f center(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
    m_buttonText.setOrigin(center);

}

void Button::ButtonUpdate(sf::Vector2i mousePos)
{

    if(m_buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        m_buttonShape.setOutlineColor(sf::Color::White);
        m_hovered = true;
    }else
    {
        m_buttonShape.setOutlineColor(m_buttonColor);
        m_hovered = false;
    }
}

void Button::Activate()
{
    if(m_hovered && callback != nullptr)
    {
        callback();
    }
}
