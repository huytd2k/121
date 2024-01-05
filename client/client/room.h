#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Room {
public:
    sf::Text text;
    sf::RectangleShape border;


    Room(const std::string& buttonText, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position)
        : text(buttonText, font, characterSize) {
        text.setFillColor(sf::Color::Black);
        text.setPosition(position);

        // Set up border
        sf::FloatRect textBounds = text.getGlobalBounds();
        border.setSize(sf::Vector2f(textBounds.width + 20.0f, textBounds.height + 10.0f));
        border.setPosition(position.x - 10.0f, position.y - 5.0f);
        border.setOutlineThickness(2.0f);
        border.setOutlineColor(sf::Color::White);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(border);
        window.draw(text);
    }
    std::string getString() {
        return text.getString();
    }
    bool isMouseOver(const sf::RenderWindow& window) const {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f borderPosition = border.getPosition();
        sf::Vector2f rectSize = border.getSize();

        return (mousePosition.x >= borderPosition.x && mousePosition.x <= borderPosition.x + rectSize.x &&
            mousePosition.y >= borderPosition.y && mousePosition.y <= borderPosition.y + rectSize.y);
    }
};