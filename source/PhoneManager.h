#ifndef _PHONE_MANAGER_H_
#define _PHONE_MANAGER_H_

#include "WindowState.hpp"
#include "Popup.h"
#include "app.h"

class PhoneManager
{
private:
    // Video mode
    sf::RenderWindow window;

    // States
    WindowState *currentState;
    MainMenuState *menu;
public:
    ~PhoneManager();
    void initWindow();
    bool isWindowOpen();
    void initMainMenuState();

    // States
    void setState(WindowState *state);
    MainMenuState *getMenuState();

    WindowState *getCurrentState();
    //sf::Sound &getSelectionSound();
    void drawCurrentState();

    // Window process
    void clearScreen();
    void pollEvents();
    void update();
    void draw();
    sf::RenderWindow &getRenderWindow();
};

#endif