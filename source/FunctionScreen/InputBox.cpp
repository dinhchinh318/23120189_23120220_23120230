#include "InputBox.h"

InputBox::InputBox(sf::Font& fontRef, sf::Vector2f position, sf::Vector2f size, const std::string& placeholderText)
    : font(fontRef), placeholder(placeholderText)
{
    box.setPosition(position);
    box.setSize(size);
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);

    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color(150, 150, 150));  // Màu placeholder nhạt hơn
    text.setString(placeholder);
    text.setPosition(position.x + 5.f, position.y + (size.y - text.getCharacterSize()) / 2.f);
    showingPlaceholder = true;
}

void InputBox::setPosition(float x, float y)
{
    box.setPosition(x, y);
    sf::Vector2f size = box.getSize();
    text.setPosition(x + 5.f, y + (size.y - text.getCharacterSize()) / 2.f);
}

void InputBox::handleEvent(const sf::Event& event)
{
    if (!isActive)
        return;

    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode == 8) // Backspace
        {
            std::string str = text.getString();
            if (!str.empty())
            {
                str.pop_back();
                if (str.empty()) {
                    showingPlaceholder = true;
                    text.setFillColor(sf::Color(150, 150, 150));
                    text.setString(placeholder);
                } else {
                    text.setString(str);
                }
            }
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 128) // Các ký tự hiển thị được
        {
            if (showingPlaceholder) {
                text.setString("");
                showingPlaceholder = false;
                text.setFillColor(sf::Color::Black);
            }
            std::string str = text.getString();
            str += static_cast<char>(event.text.unicode);
            text.setString(str);
        }
    }
}

void InputBox::update(const sf::Vector2f& mousePos)
{
    if (box.getGlobalBounds().contains(mousePos))
        box.setOutlineColor(sf::Color::Blue);
    else
        box.setOutlineColor(isActive ? sf::Color::Red : sf::Color::Black);
}

bool InputBox::isClicked(const sf::Vector2f& mousePos) const
{
    return box.getGlobalBounds().contains(mousePos);
}

std::string InputBox::getText() const
{
    if (showingPlaceholder)
        return "";
    return text.getString();
}

void InputBox::setText(const std::string& str)
{
    if (str.empty()) {
        showingPlaceholder = true;
        text.setFillColor(sf::Color(150, 150, 150));
        text.setString(placeholder);
    } else {
        showingPlaceholder = false;
        text.setFillColor(sf::Color::Black);
        text.setString(str);
    }
}

void InputBox::activate()
{
    isActive = true;
    if (showingPlaceholder) {
        text.setString("");
        text.setFillColor(sf::Color::Black);
        showingPlaceholder = false;
    }
}

void InputBox::deactivate()
{
    isActive = false;
    if (text.getString().isEmpty()) {
        showingPlaceholder = true;
        text.setFillColor(sf::Color(150, 150, 150));
        text.setString(placeholder);
    }
}

void InputBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(box, states);
    target.draw(text, states);
}
void InputBox:: handleTextInput(sf::Uint32 unicode) {
    if (unicode == 8) { // Backspace
        if (!Text.empty())
            Text.pop_back();
    }
    else if (unicode >= 32 && unicode <= 126) { // Chỉ nhận ký tự ASCII in được
        Text += static_cast<char>(unicode);
    }

    // Cập nhật nội dung hiển thị
    TextDisplay.setString(Text);
}

void InputBox::pollEvent(sf::RenderWindow& window, sf::Event& event) {
    // Kích hoạt khi click chuột vào box
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (isClicked(mousePos)) activate();
        else deactivate();
    }
    // Xử lý nhập ký tự khi đang active
    if (isActive) {
        if (event.type == sf::Event::TextEntered) {
            handleTextInput(event.text.unicode);
        }
        // Có thể bổ sung xử lý phím Backspace, Enter, v.v. nếu cần
    }
}
