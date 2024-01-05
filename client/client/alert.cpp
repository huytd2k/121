#include "alert.h"

MessageBox1::MessageBox1(const std::string& text, const sf::Font& font, unsigned int fontSize, const sf::Vector2f& position) {
    message.setString(text);
    message.setFont(font);
    message.setCharacterSize(fontSize);
    message.setPosition(position);
    message.setFillColor(sf::Color::White);
}

void MessageBox1::draw(sf::RenderWindow& window) {
    window.draw(message);
}