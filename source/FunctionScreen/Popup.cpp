// Popup.cpp
#include "Popup.h"

Popup::Popup(float windowWidth, float windowHeight) {
    font.loadFromFile("Fonts/ARIAL.ttf");

    // if (backgroundTexture.loadFromFile("Pictures/popupImage.png")) {
    //     background.setSize(sf::Vector2f(400, 100));
    //     background.setTexture(&backgroundTexture);
    // }
    
    background.setSize(sf::Vector2f(400, 100));
    background.setFillColor(sf::Color::Black); // Màu nền trắng
    background.setOutlineThickness(2);         // Độ dày viền
    background.setOutlineColor(sf::Color::White); // Viền đen

    background.setOrigin(background.getSize() / 2.0f);
    background.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);

    message.setFont(font);
    message.setCharacterSize(24);
    message.setFillColor(sf::Color::White);
}

void Popup::show(const std::string& msg, sf::Color color, float durationSec) {
    message.setString(msg);
    message.setFillColor(color);
    
    float paddingX = 40.f;
    float paddingY = 20.f;

    sf::FloatRect textBounds = message.getLocalBounds();
    float boxWidth = textBounds.width + paddingX * 2;
    float boxHeight = textBounds.height + paddingY * 2;

    background.setSize(sf::Vector2f(boxWidth, boxHeight));
    background.setOrigin(boxWidth / 2.f, boxHeight / 2.f);

    // Căn giữa popup gần đáy
    float centerX = background.getPosition().x;
    float bottomY = background.getPosition().y;

    // Cập nhật vị trí message nằm giữa trong background
    message.setPosition(
        centerX - textBounds.width / 2.f - textBounds.left,
        bottomY - textBounds.height / 2.f - textBounds.top
    );

    duration = durationSec;
    clock.restart();
    visible = true;
}


void Popup::update() {
    if (visible && clock.getElapsedTime().asSeconds() > duration) {
        visible = false;
    }
}

void Popup::draw(sf::RenderWindow& window) {
    if (visible) {
        window.draw(background);
        window.draw(message);
    }
}

bool Popup::isVisible() const {
    return visible;
}
