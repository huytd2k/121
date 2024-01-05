#include "addRoom.h"



void AddRoom::setOnClick(std::function<void()> onClick) {
    this->onClick = onClick;
}

bool AddRoom::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    return shape.getGlobalBounds().contains(mousePosition);
}

void AddRoom::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOver(window)) {
            onClick();
        }
    }
}