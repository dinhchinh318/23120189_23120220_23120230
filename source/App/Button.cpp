#include "Button.h"

Button::Button(const std::string& label, sf::Vector2f pos, sf::Vector2f size, sf::Font& f, UITheme theme)
    : font(f), theme(theme), currentColor(theme.buttonColor) {

    // Setup shape
    shape.setPosition(pos);
    shape.setSize(size);
    shape.setFillColor(currentColor);
    shape.setOutlineColor(theme.borderColor);
    shape.setOutlineThickness(theme.outlineThickness);

    // Setup text
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(theme.characterSize); // Cho phép lấy từ theme nếu có
    text.setFillColor(theme.textColor);

    centerText();
}


void Button::setFont(sf::Font &font)
{
    text.setFont(font);
}

void Button::setTextSize(unsigned int size)
{
    text.setCharacterSize(size);
}

void Button::setTextColor(sf::Color color)
{
    text.setFillColor(color);
}

void Button::setTitle(std::string str)
{
    text.setString(str);
}

void Button::setBackgroundColor(sf::Color color)
{
    shape.setFillColor(color);
}

void Button::setPosition(float x, float y)
{
    this->setOriginToCenter();
    this->setOriginToCenterForText();

    shape.setPosition(x, y);
    text.setPosition(x, y);
}

void Button::setSize(float width, float height)
{
    shape.setSize({width, height});
}

void Button::setScale(float w, float h) {
    this->shape.setScale(w, h);
}

void Button::setTexture(sf::Texture& texture) {
    this->shape.setTexture(&texture);
}

int Button::getLocalBoundsWidth()
{
    return this->shape.getLocalBounds().width;
}

int Button::getLocalBoundsHeight()
{
    return this->shape.getLocalBounds().height;
}

int Button::getPositionX()
{
    return this->shape.getPosition().x;
}

int Button::getPositionY()
{
    return this->shape.getPosition().y;
}

int Button::getSizeWidth()
{
    return this->shape.getSize().x;
}

int Button::getSizeHeight()
{
    return this->shape.getSize().y;
}

void Button::setOriginToCenter() {
    this->shape.setOrigin(this->shape.getLocalBounds().width/2, this->shape.getLocalBounds().height/2);
}

void Button::setOriginToCenterForText() {
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
}

bool Button::isMouseOver(sf::RenderWindow &window)
{

    float xMouse = sf::Mouse::getPosition(window).x;
    float yMouse = sf::Mouse::getPosition(window).y;

    float topLeftX = shape.getPosition().x - shape.getLocalBounds().width / 2;
    float topLeftY = shape.getPosition().y - shape.getLocalBounds().height / 2;

    float limitRangeX = topLeftX + shape.getLocalBounds().width;
    float limitRangeY = topLeftY + shape.getLocalBounds().height;

    // std::cout << "mouse: " << xMouse << " "  << yMouse << std::endl;
    // std::cout << "limit: " << limitRangeX << " " << limitRangeY << std::endl;

    if (topLeftX < xMouse && xMouse < limitRangeX && topLeftY < yMouse && yMouse < limitRangeY)
    {
        return true;
    }
    return false;
}

void Button::centerText() {
    auto bounds = text.getLocalBounds(); // Lấy kích thước thật sự của chữ
    text.setOrigin(bounds.left + bounds.width / 2.0f,
                   bounds.top + bounds.height / 2.0f); // Đặt tâm chữ là chính giữa

    sf::Vector2f shapePos = shape.getPosition(); // Lấy vị trí nút
    sf::Vector2f shapeSize = shape.getSize();    // Lấy kích thước nút

    // Căn chữ vào giữa nút
    text.setPosition(shapePos.x + shapeSize.x / 2.0f,
                     shapePos.y + shapeSize.y / 2.0f);
}

void Button::drawTo(sf::RenderWindow &window)
{
    window.draw(shape);
    window.draw(text);
}