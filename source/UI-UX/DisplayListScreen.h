#ifndef _DISPLAY_LIST_SCREEN_H_
#define _DISPLAY_LIST_SCREEN_H_

#include "BaseScreen.h"

class DisplayListScreen : public BaseScreen 
{
public:
    DisplayListScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
    void draw(sf::RenderWindow& window, sf::Font& font) override;
};

#endif