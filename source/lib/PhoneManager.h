#ifndef _PHONE_MANAGER_H_
#define _PHONE_MANAGER_H_

#include "app.h"
#include "WindowState.hpp"
#include "Popup.h"

class SettingState;
class MainMenu;
enum PlayMode
{
    PLAYER,
    BOT
};

class PhoneManager
{
private:
    // Video mode
    sf::RenderWindow window;

    sf::Image AppIcon;
    PlayMode playMode;

    // States
    WindowState *currentState;
    MainMenuState *menu;
    SettingState *setting;
    ///////////////////////////////
    PhoneManagementState *phone;

    // Popups
    sf::Font popupFont;
    sf::Texture popupTexture;
    ///////////////////////////////
    // Popup saveGamePopup;
    // Popup backMainMenuPopup;
    // Popup saveGameToCreatANewOne;
    // Popup chooseMode;

    // Music
    sf::Music bg_music;
    sf::SoundBuffer selectionSoundBuffer;
    sf::Sound selectionSound;

    // Volume
    int bg_musicVol;
    int soundEffectVol;

public:
    // signs to be used in states
    /////////////////////////////
    // bool hasGameInProgress;
    // bool showPlayModePopup;
    // bool showSaveGamePopup;
    // bool showSaveGamePopup2;
    // bool showBackMenuPopup;
    // Graphics
    ~PhoneManager();
    void initWindow();
    bool isWindowOpen();
    /////////////////////////////
    void initPhoneManagementState();
    void initMainMenuState();
    void initSettingState();
    // States
    void setState(WindowState *state);
    MainMenuState *getMenuState();
    SettingState *getSettingState();
    PhoneManagementState *getPhoneManagementState();
    WindowState *getCurrentState();
    sf::Sound &getSelectionSound();
    void drawCurrentState();
    // Window process
    void clearScreen();
    void pollEvents();
    void update();
    void draw();
    sf::RenderWindow &getRenderWindow();
    // Popups
    void initPopup();
    void pollPopUpEvent();
    void updatePopup();
    void drawPopup();
    // Music and sound
    void setBGMusicVol(int volume);
    void setSoundEffectVol(int volume);
    int getSoundEffectVolume();
};

#endif