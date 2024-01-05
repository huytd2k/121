#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class AddRoom {
public:
    sf::Text text;
    sf::CircleShape border;


    AddRoom(const std::string& buttonText, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position)
        : text(buttonText, font, characterSize) {
        text.setFillColor(sf::Color::Red);
        text.setPosition(position);

        // Set up border
        sf::FloatRect textBounds = text.getGlobalBounds();
        border.setRadius(30.f);
        border.setPosition(position.x - 10.0f, position.y - 10.0f);
        border.setOutlineThickness(2.0f);
        border.setOutlineColor(sf::Color::White);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(border);
        window.draw(text);
    }
    bool isMouseOver(const sf::RenderWindow& window) const {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f borderPosition = border.getPosition();
        float borderRadius = border.getRadius();

        float dx = mousePosition.x - (borderPosition.x + borderRadius);
        float dy = mousePosition.y - (borderPosition.y + borderRadius);

        return (dx * dx + dy * dy) <= (borderRadius * borderRadius);
    }
};