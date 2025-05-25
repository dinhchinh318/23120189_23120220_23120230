#include "app.h"

App::App()
{
    
    
}

void App::initWindow() {
    window.create(sf::VideoMode(1500, 800), "Phone Management", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    if (!font.loadFromFile("Fonts/ARIAL.ttf")) {
        std::cerr << "Can't find font!" << std::endl;
        return;
    }

    if (!bgTexture.loadFromFile("Pictures/background1.jpg")) {
        std::cerr << "Can't load file background.jpg" << std::endl;
        return;
    }

    bgSprite.setTexture(bgTexture);
    sf::Vector2u textureSize = bgTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    bgSprite.setScale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);

    init = new InitScreen(font, theme);
    addScreen = new AddPhoneScreen(font, theme);
    displayScreen = new DisplayListScreen(font, theme);
    searchScreen = new SearchScreen(font, theme);
    findScreen = new FindListScreen(font, theme);
    deleteScreen = new DeleteScreen(font, theme);
    editScreen = new EditScreen(font, theme);
    editListScreen = new EditListScreen(font, theme);
    editExec = new EditExecute(font, theme);

    currentScreen = AppScreen::INIT_SCREEN;
}

void App::run() {
    while (window.isOpen()) {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            switch (currentScreen) {
                case AppScreen::ADD_PHONE:
                    addScreen->pollEvent(window, event, currentScreen);
                    break;
                case AppScreen::DISPLAY_LIST:
                    displayScreen->pollEvent(window, event, currentScreen);
                    break;
                case AppScreen::DELETE_PHONE:
                    deleteScreen->pollEvent(window, event, currentScreen);
                    break;
                case AppScreen::SEARCH_PHONE:
                    searchScreen->pollEvent(window, event, currentScreen);
                    pList = searchScreen->getPhone();
                    break;
                case AppScreen::FIND_LIST:
                    findScreen->pollEvent(window, event, currentScreen);
                    break;
                case AppScreen::EDIT_PHONE:
                    editScreen->pollEvent(window, event, currentScreen);
                    pList = editScreen->getPhone();
                    break;
                case AppScreen::EDIT_LIST:
                    if (pList.empty()) pList = getPhonesFromDatabase();  // <-- nếu chưa có
                    editListScreen->setPhones(pList);
                    editListScreen->pollEvent(window, event, currentScreen);
                    if (currentScreen == AppScreen::EDIT) {
                        index = editListScreen->getIndex();
                        if (index >= 0 && index < pList.size()) {
                            editExec->setPhoneToEdit(pList[index]);
                        }
                    }
                    break;
                case AppScreen::EDIT:
                    editExec->pollEvent(window, event, currentScreen);
                    break;
                case AppScreen::INIT_SCREEN:
                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                        init->handleClicked(mousePos, currentScreen, window);
                    break;
                default:
                    break;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                switch (currentScreen) {
                    case AppScreen::ADD_PHONE:
                        addScreen->handleClicked(mousePos, currentScreen, window);
                        break;
                    case AppScreen::DISPLAY_LIST:
                        displayScreen->handleClicked(mousePos, currentScreen, window);
                        break;
                    case AppScreen::SEARCH_PHONE:
                        searchScreen->handleClicked(mousePos, currentScreen, window);
                        break;
                    case AppScreen::FIND_LIST:
                        findScreen->handleClicked(mousePos, currentScreen, window);
                        break;
                    case AppScreen::DELETE_PHONE:
                        deleteScreen->handleClicked(mousePos, currentScreen, window);
                        break;
                    case AppScreen::EDIT_PHONE:
                        editScreen->handleClicked(mousePos, currentScreen, window);
                        break;
                    case AppScreen::EDIT_LIST:
                        editListScreen->handleClicked(mousePos, currentScreen, window);
                        break;
                    case AppScreen::EDIT:
                        editExec->handleClicked(mousePos, currentScreen, window);
                        break;
                    default:
                        break;
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && currentScreen == AppScreen::FIND_LIST)
            {
                currentScreen = AppScreen::SEARCH_PHONE;
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && currentScreen == AppScreen::EDIT_LIST)
            {
                currentScreen = AppScreen::EDIT_PHONE;
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && currentScreen == AppScreen::EDIT)
            {
                currentScreen = AppScreen::EDIT_LIST;
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                currentScreen = AppScreen::INIT_SCREEN;
            }
        }

        window.clear();
        window.draw(bgSprite);

        switch (currentScreen) {
            case AppScreen::INIT_SCREEN:
                init->update(mousePos);
                init->draw(window, font, currentScreen);
                break;
            case AppScreen::ADD_PHONE:
                addScreen->update(mousePos);
                addScreen->draw(window, font, currentScreen);
                break;
            case AppScreen::DISPLAY_LIST:
                displayScreen->update(mousePos);
                displayScreen->draw(window, font, currentScreen);
                break;
            case AppScreen::SEARCH_PHONE:
                searchScreen->update(mousePos);
                searchScreen->draw(window, font, currentScreen);
                break;
            case AppScreen::FIND_LIST:
                findScreen->setPhones(pList);
                findScreen->update(mousePos);
                findScreen->draw(window, font, currentScreen);
                break;
            case AppScreen::DELETE_PHONE:
                deleteScreen->update(mousePos);
                deleteScreen->draw(window, font, currentScreen);
                break;
            case AppScreen::EDIT_PHONE:
                editScreen->update(mousePos);
                editScreen->draw(window, font, currentScreen);
                break;
            case AppScreen::EDIT_LIST:
                editListScreen->setPhones(pList);
                editListScreen->update(mousePos);
                editListScreen->draw(window, font, currentScreen);
                break;
            case AppScreen::EDIT:
                editExec->update(mousePos);
                editExec->draw(window, font, currentScreen);
                break;
        }

        window.display();
    }
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
    if (this->editExec)
        delete this->editExec;
}