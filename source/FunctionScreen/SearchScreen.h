#ifndef _SEARCH_SCREEN_H_
#define _SEARCH_SCREEN_H_

#include "../Screen/BaseScreen.h"

class SearchScreen : public BaseScreen 
{
public:
    SearchScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
    void draw(sf::RenderWindow& window, sf::Font& font) override;
};

#endif