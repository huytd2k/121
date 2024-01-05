#include "tetris2.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "network.h"

#include <iostream>
Tetris2::~Tetris2() {
    // Hủy các tài nguyêt
    // ...
}
sf::RectangleShape divider;
Tetris2::Tetris2(int socket, std::string name) {

    gameSocket = socket;
    roomName = name;
    sendResult = false;
    

    areaEnermy.resize(lines);
    for (std::size_t i{}; i < areaEnermy.size(); ++i) {
        areaEnermy[i].resize(cols);
    }

    area.resize(lines);
    for (std::size_t i{}; i < area.size(); ++i) {
        area[i].resize(cols);
    }

    forms = {
      {1,3,5,7}, // I
      {2,4,5,7}, // Z
      {3,5,4,6}, // S
      {3,5,4,7}, // T
      {2,3,5,7}, // L
      {3,5,7,6}, // J
      {2,3,4,5}, // O
    };

    window = std::make_shared<sf::RenderWindow>(
        //sf::VideoMode(724, 720),
        sf::VideoMode(360, 720),
        "Tetris 2 player (remix)",
        sf::Style::Titlebar | sf::Style::Close
    );
    window->setPosition(sf::Vector2i(300, 100));

    tiles.loadFromFile("images/squares.png");
    sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(tiles);
    sprite->setTextureRect(sf::IntRect(0, 0, 36, 36));

    bg.loadFromFile("images/background1.png");
    background = std::make_shared<sf::Sprite>();
    background->setTexture(bg);
    
    bg1.loadFromFile("images/background1.png");
    background1 = std::make_shared<sf::Sprite>();
    background1->setTexture(bg1);

    background->setPosition(0, 0);
    background1->setPosition(360, 0);


    // Tạo divider
    
    divider.setSize(sf::Vector2f(4,720));
    divider.setFillColor(sf::Color::Blue);
    divider.setPosition(360, 0);

    dirx = score = { 0 };
    rotate = gameover = { false };
    timercount = { 0.f };
    delay = { 0.3f };
    color = { 1 };

    std::uint32_t number = std::rand() % shapes;
    for (std::size_t i{}; i < squares; ++i) {
        z[i].x = forms[number][i] % 2;
        z[i].y = forms[number][i] / 2;
    }

    font.loadFromFile("font/font.ttf");
    txtScore.setFont(font);
    txtScore.setPosition(100.f, 10.f);
    txtScore.setString("SCORE: " + std::to_string(score));
    txtScore.setCharacterSize(30);
    txtScore.setOutlineThickness(3);

    txtGameOver.setFont(font);
    txtGameOver.setPosition(30.f, 300.f);
    txtGameOver.setString("GAME OVER");
    txtGameOver.setCharacterSize(50);
    txtGameOver.setOutlineThickness(3);

    textResult.setFont(font);
    textResult.setPosition(30.f, 400.f);
    textResult.setCharacterSize(50);
    textResult.setOutlineThickness(3);

}

void Tetris2::events() {

    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timercount += time;
    

    auto e = std::make_shared<sf::Event>();
    while (window->pollEvent(*e)) {
        if (e->type == sf::Event::Closed) {
            if (!gameover) {
                score = -10;
            }
            window->close();
            gameOverCallback(score);
        }

        if (e->type == sf::Event::KeyPressed) {
            if (e->key.code == sf::Keyboard::Up) {
                rotate = true;
            }
            else if (e->key.code == sf::Keyboard::Right) {
                ++dirx;
            }
            else if (e->key.code == sf::Keyboard::Left) {
                --dirx;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        delay = 0.05f;
    }
}


void Tetris2::receiveData() {
    for (std::size_t i{}; i < lines; ++i) {
        for (std::size_t j{}; j < cols; ++j) {
            if (areaEnermy[i][j] != 0) {
                sprite->setTextureRect(sf::IntRect(area[i][j] * 36, 0, 36, 36));
                sprite->setPosition((j + cols) * 36, i * 36);
                window->draw(*sprite);

            }
        }
    }
}

// Hàm gửi dữ liệu qua socket
bool Tetris2::sendVector2D(int socket, const std::vector<std::vector<std::uint32_t>>& data) {
    std::size_t rows = 20;
    std::size_t cols = 10;

    // Gửi dữ liệu của mảng
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            std::uint32_t value = data[i][j];
            if (sendWrapper(socket, reinterpret_cast<const char*>(&value), sizeof(value), 0) == -1) {
                return false;
            }
        }
    }

    return true;
}





void Tetris2::draw() {
    window->clear(sf::Color::Black);
    window->draw(*background);
    //window->draw(*background1);
    window->draw(divider);

    for (std::size_t i{}; i < lines; ++i) {
        for (std::size_t j{}; j < cols; ++j) {
            if (area[i][j] != 0) {
                sprite->setTextureRect(sf::IntRect(area[i][j] * 36, 0, 36, 36));
                sprite->setPosition(j * 36, i * 36);
                window->draw(*sprite);

            }
        }
    }

    for (std::size_t i{}; i < squares; ++i) {
        sprite->setTextureRect(sf::IntRect(color * 36, 0, 36, 36));
        sprite->setPosition(z[i].x * 36, z[i].y * 36);
        window->draw(*sprite);
    }
   

    window->draw(txtScore);
    if (gameover) {
        
        window->draw(txtGameOver);

        if (!sendResult) {
            sendResult = true;
            std::string inter = "SCORE";
            std::string message = inter + "||" + std::to_string(score) + "||" + roomName;
            std::cout << score << "--" << roomName << "\n";
            sendWrapper(gameSocket, message.c_str(), message.size(), 0);
            char buffer[1024];
            int bytesRead = recv(gameSocket, buffer, sizeof(buffer), 0);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0';
                std::string messFromServer = std::string(buffer, bytesRead);
                std::string messInfo0 = messFromServer.substr(0, 3);
                std::string messInfo1 = messFromServer.substr(5, 1);
            
                if (messInfo0 == "+OK") {
                    if (messInfo1 == "W") {
                        textResult.setString("Winner");
                        textResult.setFillColor(sf::Color(255, 165, 0));
                    }
                    else if (messInfo1 == "D") {
                        textResult.setString("Draw");
                        textResult.setFillColor(sf::Color::Green);
                    }
                    else if (messInfo1 == "L") {
                        textResult.setString("Loser");
                        textResult.setFillColor(sf::Color::Red);
                    }
                    else if (messInfo1 == "C") {
                        textResult.setString("Winner\nPartner is disconncted");
                        textResult.setFillColor(sf::Color::Blue);
                        textResult.setCharacterSize(20);
                        
                    }
                }
            }
        }
        window->draw(textResult);
  
    }
    window->display();
}


void Tetris2::run() {
    while (window->isOpen()) {
        events();
        if (!gameover) {
            changePosition();
            setRotate();
            moveToDown();
            setScore();
            resetValues();
        }
        else {
            if (gameOverCallback) {
                gameOverCallback(score);
            }
        }
        draw();
    }
}

void Tetris2::setGameOverCallback(std::function<void(int)> callback) {
    gameOverCallback = callback;
}
int Tetris2::getScore() const {
    return score;
}

void Tetris2::moveToDown() {
    if (timercount > delay) {
        for (std::size_t i{}; i < squares; ++i) {
            k[i] = z[i];
            ++z[i].y;
        }

        if (maxLimit()) {

            for (std::size_t i{}; i < squares; ++i) {
                area[k[i].y][k[i].x] = color;
            }

            color = std::rand() % shapes + 1;
            std::uint32_t number = std::rand() % shapes;
            for (std::size_t i{}; i < squares; ++i) {
                z[i].x = forms[number][i] % 2;
                z[i].y = forms[number][i] / 2;
            }
        }

        timercount = 0;
    }

}

void Tetris2::setRotate() {
    if (rotate) {
        Coords coords = z[1];
        for (std::size_t i{}; i < squares; ++i) {
            int x = z[i].y - coords.y;
            int y = z[i].x - coords.x;

            z[i].x = coords.x - x;
            z[i].y = coords.y + y;
        }

        if (maxLimit()) {
            for (std::size_t i{}; i < squares; ++i) {
                z[i] = k[i];
            }
        }
    }
}

void Tetris2::resetValues() {
    dirx = 0;
    rotate = false;
    delay = 0.3f;
}

void Tetris2::changePosition() {
    for (std::size_t i{}; i < squares; ++i) {
        k[i] = z[i];
        z[i].x += dirx;
    }

    if (maxLimit()) {
        for (std::size_t i{}; i < squares; ++i) {
            z[i] = k[i];
        }
    }
}

bool Tetris2::maxLimit() {
    for (std::size_t i{}; i < squares; ++i) {
        if (z[i].x < 0 ||
            z[i].x >= cols ||
            z[i].y >= lines ||
            area[z[i].y][z[i].x]) {
            return true;
        }
    }
    return false;
}

void Tetris2::setScore() {
    std::uint32_t match = lines - 1;
    for (std::size_t i = match; i >= 1; --i) {
        std::uint32_t sum{};
        for (std::size_t j{}; j < cols; ++j) {
            if (area[i][j]) {
                if (i == 1) {
                    gameover = true;
                }
                ++sum;
            }
            area[match][j] = area[i][j];
        }
        if (sum < cols) {
            --match;
        }
        else {
            txtScore.setString("SCORE: " + std::to_string(++score));
        }
    }
}