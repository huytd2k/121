#pragma once

#include <SFML/Graphics.hpp>

class MessageBox1 {
public:
    MessageBox1(const std::string& text, const sf::Font& font, unsigned int fontSize, const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);

private:
    sf::Text message;
    
};