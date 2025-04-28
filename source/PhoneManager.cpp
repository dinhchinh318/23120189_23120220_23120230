#include "PhoneManager.h"

PhoneManager::~PhoneManager()
{
    if (this->menu)
        delete this->menu;
}

void PhoneManager::initWindow()
{

    this->window.create(sf::VideoMode(1200, 800), "PhoneManagement", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(90);

    // Creat and load 2 states
    this->initMainMenuState();

    this->currentState = this->menu;
}

bool PhoneManager::isWindowOpen()
{
    return this->window.isOpen();
}

void PhoneManager::initMainMenuState()
{
    this->menu = new MainMenuState;
    this->menu->init(this);
}

void PhoneManager::setState(WindowState *state)
{
    this->currentState = state;
}


MainMenuState *PhoneManager::getMenuState()
{
    return this->menu;
}

WindowState *PhoneManager::getCurrentState()
{
    return this->currentState;
}

void PhoneManager::clearScreen()
{
    this->window.clear();
}

void PhoneManager::drawCurrentState()
{
    // this->windowState->pollEvents(this); ??
    this->currentState->draw(this);
}

sf::RenderWindow &PhoneManager::getRenderWindow()
{
    return this->window;
}