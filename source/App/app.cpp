#include "app.h"

void App::initWindow()
{
    // Init window
    this->window.create(sf::VideoMode(1500, 800), "Phone Management", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(60);

    // Init Font
    if (!font.loadFromFile("Fonts/ARIAL.ttf")) 
    {
        std::cerr << "Can't find font!" << std::endl;
        return;
    }

    // Init and set background
    if (!bgTexture.loadFromFile("Pictures/background1.jpg")) 
    {
        std::cerr << "Can't load file background.jpg" << std::endl;
        return;
    }
    bgSprite.setTexture(bgTexture);
    sf::Vector2u textureSize = bgTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    bgSprite.setScale(
        float(windowSize.x) / textureSize.x,
        float(windowSize.y) / textureSize.y
    );

    // Init Screen
    init = new InitScreen(font, theme);
    addScreen = new AddPhoneScreen(font, theme);
    displayScreen = new DisplayListScreen(font, theme);
    searchScreen = new SearchScreen(font, theme);
    findScreen = new FindListScreen(font, theme);
    deleteScreen = new DeleteScreen(font, theme);
    editScreen = new EditScreen(font, theme);
    editListScreen = new EditListScreen(font, theme);

    // Set Screen default
    currentScreen = AppScreen::INIT_SCREEN;
}

void App::run()
{
    while (window.isOpen())  
    {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (currentScreen == AppScreen::ADD_PHONE) {
                addScreen->pollEvent(window, event);
            }
            if (currentScreen == AppScreen::DISPLAY_LIST) {
                displayScreen->pollEvent(window, event);
            }
            if (currentScreen == AppScreen::DELETE_PHONE) {
                deleteScreen->pollEvent(window, event);
            }
            if (currentScreen == AppScreen::SEARCH_PHONE) {
                searchScreen->pollEvent(window, event);
                pList = searchScreen->getPhone();
            }
            if (currentScreen == AppScreen::FIND_LIST) {
                findScreen->pollEvent(window, event);
            }
            if (currentScreen == AppScreen::EDIT_PHONE) {
                editScreen->pollEvent(window, event);
                pList = editScreen->getPhone();
            }
            if (currentScreen == AppScreen::EDIT_LIST) {
                editListScreen->pollEvent(window, event);
            }


            if (currentScreen == AppScreen::SEARCH_PHONE && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                searchScreen->handleClick(mousePos, currentScreen, window);
            }
            
            if (currentScreen == AppScreen::EDIT_PHONE && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                editScreen->handleClick(mousePos, currentScreen, window);
            }

            if (currentScreen == AppScreen::INIT_SCREEN &&
                event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) 
            {
                init->handleClicked(mousePos, currentScreen, window);
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
            {
                if (currentScreen == AppScreen::ADD_PHONE)
                {
                    addScreen->handleClicked(mousePos, currentScreen, window);
                }
                else if (currentScreen == AppScreen::DISPLAY_LIST)
                {
                    displayScreen->handleClicked(mousePos, currentScreen, window);
                }
                else if (currentScreen == AppScreen::SEARCH_PHONE)
                {
                    searchScreen->handleClicked(mousePos, currentScreen, window);
                }
                else if (currentScreen == AppScreen::FIND_LIST)
                {
                    findScreen->handleClicked(mousePos, currentScreen, window);
                }
                else if (currentScreen == AppScreen::DELETE_PHONE)
                {
                    deleteScreen->handleClicked(mousePos, currentScreen, window);
                }
                else if (currentScreen == AppScreen::EDIT_PHONE)
                {
                    editScreen->handleClicked(mousePos, currentScreen, window);
                }
                else if (currentScreen == AppScreen::EDIT_LIST)
                {
                    editListScreen->handleClicked(mousePos, currentScreen, window);
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
            {
                currentScreen = AppScreen::INIT_SCREEN;
            }
        }

        window.clear();
        window.draw(bgSprite);

        if (currentScreen == AppScreen::INIT_SCREEN) 
        {
            init->update(mousePos);
            init->draw(window, font, currentScreen);
        }
        else if (currentScreen == AppScreen::ADD_PHONE) 
        {
            addScreen->draw(window, font, currentScreen);
            addScreen->update(mousePos);
        }
        else if (currentScreen == AppScreen::DISPLAY_LIST) 
        {
            displayScreen->draw(window, font, currentScreen);
            displayScreen->update(mousePos);
        }
        else if (currentScreen == AppScreen::SEARCH_PHONE) 
        {
            searchScreen->draw(window, font, currentScreen);
            searchScreen->update(mousePos);  
        }
        else if (currentScreen == AppScreen::FIND_LIST) 
        {
            findScreen->setPhones(pList);
            findScreen->draw(window, font, currentScreen);
            findScreen->update(mousePos);
        }
        else if (currentScreen == AppScreen::DELETE_PHONE) 
        {
            deleteScreen->draw(window, font, currentScreen);
            deleteScreen->update(mousePos);
        }
        else if (currentScreen == AppScreen::EDIT_PHONE) 
        {
            editScreen->draw(window, font, currentScreen);
            editScreen->update(mousePos);
        }
        
        else if (currentScreen == AppScreen::EDIT_LIST) 
        {
            editListScreen->setPhones(pList);
            editListScreen->draw(window, font, currentScreen);
            editListScreen->update(mousePos);
        }

        window.display();
    }
}

App::App()
{
    
}

App::~App()
{
    if (this->init)
        delete this->init;
    if (this->addScreen)
        delete this->addScreen;
    if (this->displayScreen)
        delete this->displayScreen;
    if (this->searchScreen)
        delete this->searchScreen;
    if (this->deleteScreen)
        delete this->deleteScreen;
    if (this->editScreen)
        delete this->editScreen;
    if (this->findScreen)
        delete this->findScreen;
    if (this->editListScreen)
        delete this->editListScreen;
}