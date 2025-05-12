#ifndef _ADD_PHONE_SCREEN_H_
#define _ADD_PHONE_SCREEN_H_

#include "BaseScreen.h"

class AddPhoneScreen : public BaseScreen 
{
public:
    AddPhoneScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
    void draw(sf::RenderWindow& window, sf::Font& font) override;
};

#endif