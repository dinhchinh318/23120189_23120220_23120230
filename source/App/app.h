#ifndef _APP_H_
#define _APP_H_

#include "../FunctionScreen/InitScreen.h"
#include "../FunctionScreen/addScreen.h"
#include "../FunctionScreen/disScreen.h"
#include "../FunctionScreen/delScreen.h"
#include "../FunctionScreen/editScreen.h"
#include "../FunctionScreen/searchScreen.h"
#include "../FunctionScreen/search-listScreen.h"
#include "../FunctionScreen/edit-listScreen.h"
#include "../FunctionScreen/edit-exec.h"


class App
{
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    UITheme theme;

    InitScreen* init;
    AddPhoneScreen* addScreen;
    DisplayListScreen* displayScreen;
    SearchScreen* searchScreen;
    FindListScreen* findScreen;
    DeleteScreen* deleteScreen;
    EditScreen* editScreen;
    EditListScreen* editListScreen;
    EditExecute* editExec;

    AppScreen currentScreen;

    sf::Event event;

    SQLHENV hEnv;
    SQLHDBC hDbc;

    vector<Phone> pList;
    int index;
public:
    App();
    void initWindow();
    void run();
    ~App();
};

#endif