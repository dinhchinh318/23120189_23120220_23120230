#ifndef _DELETE_SCREEN_H_
#define _DELETE_SCREEN_H_

#include "BaseScreen.h"

class DeleteScreen : public BaseScreen 
{
public:
    DeleteScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
    void draw(sf::RenderWindow& window, sf::Font& font) override;
};

#endif