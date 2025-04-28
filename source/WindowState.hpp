#ifndef _WINDOW_STATE_H_
#define _WINDOW_STATE_H_

#include "app.h"
#include "Button.hpp"

class PhoneManager;
class WindowState
{
public:
    virtual void init(PhoneManager *PMan) = 0;
    virtual void pollEvents(PhoneManager *PMan) = 0;
    virtual void update(PhoneManager *PMan) = 0;
    virtual void draw(PhoneManager *PMan) = 0;
};

class MainMenuState : public WindowState
{
private:
    sf::RectangleShape background;
    sf::Texture bg_texture;
    sf::Font font;
    sf::Text SystemTitle;
    int currentChoice;
    int numberOfButtons;
    Button button[5];

    // add sound effect
    sf::SoundBuffer soundBuffer;
    sf::Sound selectionSound;

public:
    void pollEvents(PhoneManager *PMan) override;
    void update(PhoneManager *PMan) override;
    void draw(PhoneManager *PMan) override;
    void init(PhoneManager *PMan) override;

    MainMenuState();
};

#endif