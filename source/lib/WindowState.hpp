#ifndef _WINDOW_STATE_H_
#define _WINDOW_STATE_H_

#include "app.h"
#include "Button.hpp"
#include "PhoneSystem.h"

class PhoneManager;
class WindowState
{
public:
    virtual void init(PhoneManager *PMan) = 0;
    virtual void pollEvents(PhoneManager *PMan) = 0;
    virtual void update(PhoneManager *PMan) = 0;
    virtual void draw(PhoneManager *PMan) = 0;
};

class PhoneManager;
class MainMenuState : public WindowState
{
private:
    sf::RectangleShape background;
    sf::Texture bg_texture;
    sf::Font font;
    sf::Text gameTitle;
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

class SettingState : public WindowState
{
private:
    Button behindBar[2];
    Button frontBar[2];

    Button backButton;

    sf::Text bar1Title;
    sf::Text bar2Title;

    sf::Texture bg_texture;
    sf::RectangleShape background;

    sf::Font font;

    int changeMusicVol;
    int changeSoundVol;

public:
    SettingState();
    void init(PhoneManager *PMan) override;
    void pollEvents(PhoneManager *PMan) override;
    void update(PhoneManager *PMan) override;
    void draw(PhoneManager *PMan) override;

    // getter and setter
    int getBarMusicVolume();
    int getBarSoundVolume();
};

class PhoneManagementState : public WindowState
{
private:
    // Mouse Position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // font
    sf::Font font;
    sf::Font fontWinGame;

    // Text
    sf::Text uiText;
    // object
    PhoneSystem *pSys;
    bool isEndGame;
    bool isReplay;
    bool isRenderWinText;
    bool isRenderCheckMate;
    bool isRenderReplaying;

    // Private Functions
    void initFonts();
    void initText();
    void initBoard();

    // buttons and their textures
    Button homeBtn;
    Button saveGameBtn;
    Button undoBtn;
    Button redoBtn;
    sf::Texture homeBtnTexture;
    sf::Texture saveGameBtnTexture;
    sf::Texture undoBtnTexture;
    sf::Texture redoBtnTexture;

    // background
    sf::RectangleShape backgroundInGame;
    sf::Texture bgInGameTexture;

public:
    // constructor, destructor
    ~PhoneManagementState();

    // Accessors
    bool running(PhoneManager *PMan);

    // Functions
    void updateEndGame();

    void updateWinText();
    void updateCheckMateText();
    void updateReplaying();
    void renderText(sf::RenderTarget &target);
    void renderCheckMateText(sf::RenderTarget &target);
    void renderReplaying(sf::RenderTarget &target);

    // State processes
    void updateMousePosition(sf::RenderWindow &window);
    void pollEvents(PhoneManager *PMan);
    void update(PhoneManager *PMan);
    void draw(PhoneManager *PMan);
    void init(PhoneManager *PMan);

    // ulity functions;
    void initButton();
    void initMenuPicture(PhoneManager *PMan);
};


#endif