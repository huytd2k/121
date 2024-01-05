#include "formAddRoom.h"
#include "textbox.h"

bool name_room = false;
bool pass_room = false;
bool type_form = false;

Form::Form(sf::RenderWindow& window) : window(window), isButtonPressed(false) {
    
    font.loadFromFile("font/arial.ttf");
    type_form = false;
    nameLabel.setFont(font);
    nameLabel.setString("Name:");
    nameLabel.setCharacterSize(20);
    nameLabel.setPosition(50, 50);
    nameLabel.setFillColor(sf::Color::Black);

    passwordLabel.setFont(font);
    passwordLabel.setString("Password:");
    passwordLabel.setCharacterSize(20);
    passwordLabel.setPosition(50, 100);
    passwordLabel.setFillColor(sf::Color::Black);

    
    textRoomName.setFont(font);
    textRoomPassword.setFont(font);
    
    textSendButton.setFont(font);
    textSendButton.setCharacterSize(25);
    textSendButton.setFillColor(sf::Color::Black);
    textSendButton.setString("Create");
    textSendButton.setPosition(255, 155);

    initButton();
}

Form::Form(sf::RenderWindow& window, std::string nameRoom) : window(window), isButtonPressed(false) {

    font.loadFromFile("font/arial.ttf");

    nameLabel.setFont(font);
    nameLabel.setString("Name:");
    nameLabel.setCharacterSize(20);
    nameLabel.setPosition(50, 50);
    nameLabel.setFillColor(sf::Color::Black);

    passwordLabel.setFont(font);
    passwordLabel.setString("Password:");
    passwordLabel.setCharacterSize(20);
    passwordLabel.setPosition(50, 100);
    passwordLabel.setFillColor(sf::Color::Black);


    textRoomName.setFont(font);
    textRoomName.setString(nameRoom);
    name = nameRoom;
    type_form = true;

    textRoomPassword.setFont(font);

    textSendButton.setFont(font);
    textSendButton.setCharacterSize(25);
    textSendButton.setFillColor(sf::Color::Black);
    textSendButton.setString("Join");
    textSendButton.setPosition(255, 155);

    initButton();
}

void Form::initButton() {
   

    sendButton.setSize(sf::Vector2f(100, 50));
    sendButton.setPosition(250, 150);
    sendButton.setFillColor(sf::Color::Green);

}

void Form::handleInput() {
    
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                if (sendButton.getGlobalBounds().contains(mousePos)) {
                    // Xử lý sự kiện khi button "Gửi" được nhấp
                    std::cout << "add room\n";
                    if (!type_form) {
                        name = textRoomName.getText();
                    }
                    password = textRoomPassword.getText();
                    std::cout << name << "-" << password << "\n";
                    if (name != "") {
                    isButtonPressed = true;
                    }
                }
                else if (nameLabel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
                    std::cout << type_form << "\n";
                    if (!type_form) {
                        name_room = true;
                        textRoomName.setSelected(true);
                    }
                    pass_room = false;
                    
                    std::cout << "input name room\n";

                }
                else if (passwordLabel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
                    pass_room = true;
                    name_room = false;
                    textRoomPassword.setSelected(true);
                    std::cout << "input passwd room\n";
                }
            }
        }
        else if (event.type == sf::Event::TextEntered ) {
            
            if (name_room) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    textRoomName.setSelected(false);
                    name_room = false;
                }
                else
                {
                    textRoomName.typedOn(event);
                }
            }
            if (pass_room) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    textRoomPassword.setSelected(false);
                    pass_room = false;
                }
                else
                {
                    textRoomPassword.typedOn(event);
                }
            }
            
        }
    }
}
void Form::draw() {
    window.draw(nameLabel);
    window.draw(passwordLabel);

    textRoomName.setPosition({150,50});
    textRoomPassword.setPosition({150,100});

    textRoomName.drawTo(window);
    textRoomPassword.drawTo(window);

    window.draw(sendButton);
    window.draw(textSendButton);
}

std::string Form::getName() const {
    return name;
}

std::string Form::getPassword() const {
    return password;
}

bool Form::isSendButtonPressed() {
    return isButtonPressed;
}

void Form::resetButtonState() {
    isButtonPressed = false;
}