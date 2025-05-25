#ifndef _INPUT_BOX_H_
#define _INPUT_BOX_H_

#include <SFML/Graphics.hpp>
#include <string>

class InputBox : public sf::Drawable
{
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Font& font;
    bool isActive = false;  // Kiểm tra xem ô có đang được nhập liệu hay không
    std::string placeholder;
    bool showingPlaceholder = true;
    std::string Text;     // lưu nội dung nhập
    sf::Text TextDisplay; 

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    InputBox(sf::Font& font, sf::Vector2f position, sf::Vector2f size, const std::string& placeholder);

    void setPosition(float x, float y);
    void handleEvent(const sf::Event& event);
    void update(const sf::Vector2f& mousePos);

    std::string getText() const;
    void setText(const std::string& str);

    bool isClicked(const sf::Vector2f& mousePos) const;

    void activate();
    void deactivate();
    void handleTextInput(sf::Uint32 unicode);


    bool getIsActive() const { return isActive; }

    // Hàm này cho phép truyền sự kiện từ window vào InputBox
    void pollEvent(sf::RenderWindow& window, sf::Event& event);
};

#endif
