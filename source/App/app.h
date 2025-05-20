#ifndef _APP_H_
#define _APP_H_

#include "../Screen/MenuScreen.h"
#include "../FunctionScreen/AddPhoneScreen.h"
#include "../FunctionScreen/DisplayListScreen.h"
#include "../FunctionScreen/DeleteScreen.h"
#include "../FunctionScreen/EditScreen.h"
#include "../FunctionScreen/SearchScreen.h"
#include "../FunctionScreen/FindListScreen.h"
#include "../FunctionScreen/EditListScreen.h"



class App
{
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    UITheme theme;

    MenuScreen* menu;
    AddPhoneScreen* addScreen;
    DisplayListScreen* displayScreen;
    SearchScreen* searchScreen;
    FindListScreen* findScreen;

    DeleteScreen* deleteScreen;
    EditScreen* editScreen;
    EditListScreen* editListScreen;

    AppScreen currentScreen;

    sf::Event event;

    SQLHENV hEnv;
    SQLHDBC hDbc;

    vector<Phone> pList;
public:
    App();
    void initWindow();
    void run();
    ~App();
};

void run();

#endif