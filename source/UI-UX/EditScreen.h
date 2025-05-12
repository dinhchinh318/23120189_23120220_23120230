#ifndef _EDIT_SCREEN_H_
#define _EDIT_SCREEN_H_

#include "BaseScreen.h"

class EditScreen : public BaseScreen 
{
public:
    EditScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
    void draw(sf::RenderWindow& window, sf::Font& font) override;
};

#endif