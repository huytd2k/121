#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "textbox.h"

class Form {
public:
    Form(sf::RenderWindow& window);
    Form(sf::RenderWindow& window, std::string nameRoom);
    void handleInput();
    void draw();
    bool isSendButtonPressed();
    void resetButtonState();

    std::string getName() const;
    std::string getPassword() const;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text nameLabel;
    sf::Text passwordLabel;

    Textbox textRoomName;
    Textbox textRoomPassword;
    

    sf::RectangleShape sendButton;
    sf::Text textSendButton;

    std::string name;
    std::string password;
    bool isButtonPressed;

    void initButton();
    
};