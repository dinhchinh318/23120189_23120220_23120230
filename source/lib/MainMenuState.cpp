#include "PhoneManager.h"
#include "WindowState.hpp"
#include "app.h"

MainMenuState::MainMenuState()
{
}

void MainMenuState::pollEvents(PhoneManager *PMan)
{
    sf::Event ev;
    while (PMan->getRenderWindow().pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            PMan->getRenderWindow().close();
        }
        else if (ev.type == sf::Event::MouseButtonPressed)
        {
            switch (this->currentChoice)
            {
            case 0:
                std::cout << "Resume" << std::endl;
                PMan->getSelectionSound().play();
                PMan->clearScreen();
                PMan->setState(PMan->getPhoneManagementState());
                break;

            // case 1:
            //     std::cout << "New game" << std::endl;
            //     PMan->getSelectionSound().play();
            //     if (PMan->hasGameInProgress && !PMan->getGameState()->endGame()) {
            //         PMan->showSaveGamePopup2 = true;
            //     }else {
            //         PMan->showPlayModePopup = true;
            //     }
            //     break;
                
            // case 2:
            //     std::cout << "Load game" << std::endl;
            //     PMan->getSelectionSound().play();
            //     if (!PMan->hasGameInProgress) {
            //         PMan->initGameState();
            //     }
            //     PMan->getGameState()->loadGame();
            //     PMan->getGameState()->resetGameState();
            //     PMan->hasGameInProgress = true;
            //     PMan->setState(PMan->getGameState());
            //     break;
                
            // case 3:
            //     std::cout << "Setting" << std::endl;
            //     PMan->getSelectionSound().play();
            //     PMan->clearScreen();
            //     PMan->setState(PMan->getSettingState());
            //     return;
            case 4:
                std::cout << "Exit" << std::endl;
                PMan->getSelectionSound().play();
                exit(2);
                break;
            default:
                break;
            }
        }
    }

    // // live mouse
    // int i = PMan->hasGameInProgress ? 0 : 1;
    // for (; i < this->numberOfButtons; ++i)
    // {
    //     if (button[i].isMouseOver(PMan->getRenderWindow()))
    //     {
    //         currentChoice = i;
    //         update(PMan);
    //         break;
    //     }
    //     currentChoice = -1;
    // }
}

void MainMenuState::init(PhoneManager *PMan)
{

    // Load sound effect
    sf::SoundBuffer soundBuffer;
    if (!this->soundBuffer.loadFromFile("Asset/selectionSound.wav"))
    {
        std::cout << "Can not load file sound effect in class MainMenu" << std::endl;
    }
    else
    {
        PMan->getSelectionSound().setBuffer(this->soundBuffer);
    }

    // Game title
    if (!this->font.loadFromFile("Asset/Pacifico.ttf"))
    {
    }
    this->background.setSize(sf::Vector2f(PMan->getRenderWindow().getSize().x,
                                          PMan->getRenderWindow().getSize().y));
    this->bg_texture.loadFromFile("Asset/bg_image.jpg");
    this->background.setTexture(&this->bg_texture);

    this->gameTitle.setString("Chess Game");
    this->gameTitle.setCharacterSize(32);
    this->gameTitle.setFont(this->font);
    this->gameTitle.setFillColor(sf::Color::Magenta);
    this->gameTitle.setOrigin(this->gameTitle.getLocalBounds().width / 2,
                              this->gameTitle.getLocalBounds().height / 2);
    this->gameTitle.setPosition(PMan->getRenderWindow().getSize().x / 2,
                                PMan->getRenderWindow().getSize().y / 2 - 200);

    // Option buttons
    this->currentChoice = 0;
    button[0].setTitle("Resume");
    button[1].setTitle("New game");
    button[2].setTitle("Load game");
    button[3].setTitle("Setting");
    button[4].setTitle("Exit");

    this->numberOfButtons = 5;
    for (int i = 0; i < numberOfButtons; ++i)
    {
        button[i].setSize(150, 30);
        button[i].setBackgroundColor(sf::Color(0, 0, 0, 0));
        button[i].setTextColor(sf::Color::White);
        button[i].setFont(this->font);
        button[i].setTextSize(28);
        button[i].setPosition(PMan->getRenderWindow().getSize().x / 2,
        PMan->getRenderWindow().getSize().y / 2 - 60 + 45 * i);
    }

}

// void MainMenuState::draw(PhoneManager *PMan)
// {
//     PMan->getRenderWindow().draw(this->background);
//     PMan->getRenderWindow().draw(this->gameTitle);

//     int i = PMan->hasGameInProgress ? 0 : 1;
//     for (; i < this->numberOfButtons; ++i)
//     {
//         button[i].drawTo(PMan->getRenderWindow());
//     }
// }

// void MainMenuState::update(PhoneManager *PMan)
// {
//     int i = PMan->hasGameInProgress ? 0 : 1;
//     for (; i < this->numberOfButtons; ++i)
//     {
//         button[i].setTextSize(20);
//         button[i].setTextColor(sf::Color::White);
//         button[i].setOriginToCenterForText();
//         if (i == currentChoice)
//         {
//             button[i].setTextSize(25);
//             button[i].setTextColor(sf::Color::Green);
//             button[i].setOriginToCenterForText();
//         }
//     }

// }