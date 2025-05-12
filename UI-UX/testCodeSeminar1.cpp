    #include <SFML/Graphics.hpp>
    #include <iostream>
    #include <vector>

    enum class AppScreen {
        MENU,
        ADD_PHONE,
        DISPLAY_LIST,
        SEARCH_PHONE,
        DELETE_PHONE,
        EDIT_PHONE
    };  

    struct UITheme {
        sf::Color background = sf::Color(34, 40, 49);
        sf::Color buttonColor = sf::Color(57, 62, 70);
        sf::Color hoverColor = sf::Color(0, 173, 181);
        sf::Color textColor = sf::Color::White;
        sf::Color textColor1 = sf::Color::Red;
        sf::Color borderColor = sf::Color(0, 173, 181);
        float borderRadius = 16.f;
        int outlineThickness = 2;
    };

    class Button {
    private:
        sf::RectangleShape shape;
        sf::Text text;
        sf::Font& font;
        UITheme theme;
        sf::Color currentColor;

    public:
        Button(const std::string& label, sf::Vector2f pos, sf::Vector2f size, sf::Font& f, UITheme theme)
            : font(f), theme(theme), currentColor(theme.buttonColor) {

            shape.setPosition(pos);
            shape.setSize(size);
            shape.setFillColor(currentColor);
            shape.setOutlineColor(theme.borderColor);
            shape.setOutlineThickness(theme.outlineThickness);

            text.setFont(font);
            text.setString(label);
            text.setCharacterSize(22);
            text.setFillColor(theme.textColor);

            auto bounds = text.getLocalBounds();
            text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
            text.setPosition(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f);
        }

        void draw(sf::RenderWindow& window) {
            shape.setFillColor(currentColor);
            window.draw(shape);
            window.draw(text);
        }

        void update(sf::Vector2f mousePos) {
            sf::Color targetColor = theme.buttonColor;
            if (shape.getGlobalBounds().contains(mousePos)) {
                targetColor = theme.hoverColor;
            }

            float factor = 0.1f;
            currentColor.r += (targetColor.r - currentColor.r) * factor;
            currentColor.g += (targetColor.g - currentColor.g) * factor;
            currentColor.b += (targetColor.b - currentColor.b) * factor;
        }

        bool isClicked(sf::Vector2f mousePos) {
            return shape.getGlobalBounds().contains(mousePos);
        }

        std::string getLabel() const {
            return text.getString();
        }
    };

    class Menu {
    private:
        std::vector<Button> buttons;
        UITheme theme;
        sf::Text title;

    public:
        Menu(sf::Font& font, UITheme theme) : theme(theme) {
            float startY = 200;
            float spacing = 70;

            title.setFont(font);
            title.setString("PHONE MANAGEMENT");
            title.setCharacterSize(32);
            title.setFillColor(theme.textColor1);
            sf::FloatRect titleBounds = title.getLocalBounds();
            title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, 0);
            title.setPosition(500, 80);

            buttons.emplace_back("ADD NEW PHONE", sf::Vector2f(365, startY + spacing * 0), sf::Vector2f(290, 50), font, theme);
            buttons.emplace_back("DISPLAY PHONE LIST", sf::Vector2f(365, startY + spacing * 1), sf::Vector2f(290, 50), font, theme);
            buttons.emplace_back("SEARCH BY NAME", sf::Vector2f(365, startY + spacing * 2), sf::Vector2f(290, 50), font, theme);
            buttons.emplace_back("DELETE BY ID", sf::Vector2f(365, startY + spacing * 3), sf::Vector2f(290, 50), font, theme);
            buttons.emplace_back("EDIT PHONE", sf::Vector2f(365, startY + spacing * 4), sf::Vector2f(290, 50), font, theme);
            buttons.emplace_back("EXIT", sf::Vector2f(365, startY + spacing * 5), sf::Vector2f(290, 50), font, theme);
        }

        void draw(sf::RenderWindow& window) {
            window.draw(title);
            for (auto& btn : buttons)
                btn.draw(window);
        }

        void update(sf::Vector2f mousePos) {
            for (auto& btn : buttons)
                btn.update(mousePos);
        }

        void handleClick(sf::Vector2f mousePos, AppScreen& screen, sf::RenderWindow& window) {
            for (auto& btn : buttons) {
                if (btn.isClicked(mousePos)) {
                    std::string label = btn.getLabel();
                    std::cout << "Clicked: " << label << std::endl;

                    if (label == "ADD NEW PHONE")
                        screen = AppScreen::ADD_PHONE;
                    else if (label == "DISPLAY PHONE LIST")
                        screen = AppScreen::DISPLAY_LIST;
                    else if (label == "SEARCH BY NAME")
                        screen = AppScreen::SEARCH_PHONE;
                    else if (label == "DELETE BY ID")
                        screen = AppScreen::DELETE_PHONE;
                    else if (label == "EDIT PHONE")
                        screen = AppScreen::EDIT_PHONE;
                    else if (label == "EXIT")
                        window.close();
                }
            }
        }
    };

    class BaseScreen {
    protected:
        Button backButton;

    public:
        BaseScreen(sf::Font& font, UITheme theme)
            : backButton("<< BACK", sf::Vector2f(20, 20), sf::Vector2f(120, 40), font, theme) {}

        virtual void draw(sf::RenderWindow& window, sf::Font& font) = 0;
        virtual bool handleBack(sf::Vector2f mousePos, AppScreen& screen) {
            if (backButton.isClicked(mousePos)) {
                screen = AppScreen::MENU;
                return true;
            }
            return false;
        }
        void drawBackButton(sf::RenderWindow& window) {
            backButton.draw(window);
        }
    };

    class AddPhoneScreen : public BaseScreen {
    public:
        AddPhoneScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
        void draw(sf::RenderWindow& window, sf::Font& font) override {
            sf::Text t("ADD NEW PHONE", font, 28);
            t.setFillColor(sf::Color::Red);
            t.setPosition(300, 100);
            window.draw(t);
            drawBackButton(window);
        }
    };

    // Tương tự cho các màn hình còn lại
    class DisplayListScreen : public BaseScreen {
    public:
        DisplayListScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
        void draw(sf::RenderWindow& window, sf::Font& font) override {
            sf::Text t("DISPLAY PHONE LIST", font, 28);
            t.setFillColor(sf::Color::Red);
            t.setPosition(250, 100);
            window.draw(t);
            drawBackButton(window);
        }
    };

    class SearchScreen : public BaseScreen {
    public:
        SearchScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
        void draw(sf::RenderWindow& window, sf::Font& font) override {
            sf::Text t("SEARCH BY NAME", font, 28);
            t.setFillColor(sf::Color::Red);
            t.setPosition(280, 100);
            window.draw(t);
            drawBackButton(window);
        }
    };

    class DeleteScreen : public BaseScreen {
    public:
        DeleteScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
        void draw(sf::RenderWindow& window, sf::Font& font) override {
            sf::Text t("DELETE BY ID", font, 28);
            t.setFillColor(sf::Color::Red);
            t.setPosition(290, 100);
            window.draw(t);
            drawBackButton(window);
        }
    };

    class EditScreen : public BaseScreen {
    public:
        EditScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
        void draw(sf::RenderWindow& window, sf::Font& font) override {
            sf::Text t("EDIT PHONE INFORMATION", font, 28);
            t.setFillColor(sf::Color::Red);
            t.setPosition(300, 100);
            window.draw(t);
            drawBackButton(window);
        }
    };

    int main() {
        sf::RenderWindow window(sf::VideoMode(1000, 800), "Quan ly dien thoai", sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);

        sf::Font font;
        if (!font.loadFromFile("VNBODO.ttf")) {
            std::cerr << "Khong tim thay font!" << std::endl;
            return -1;
        }

        sf::Texture bgTexture;
        sf::Sprite bgSprite;
        if (!bgTexture.loadFromFile("background.jpg")) {
            std::cerr << "Khong tai duoc background.jpg" << std::endl;
            return -1;
        }
        bgSprite.setTexture(bgTexture);
        sf::Vector2u textureSize = bgTexture.getSize();
        sf::Vector2u windowSize = window.getSize();
        bgSprite.setScale(
            float(windowSize.x) / textureSize.x,
            float(windowSize.y) / textureSize.y
        );

        UITheme theme;
        Menu menu(font, theme);
        AddPhoneScreen addScreen(font, theme);
        DisplayListScreen displayScreen(font, theme);
        SearchScreen searchScreen(font, theme);
        DeleteScreen deleteScreen(font, theme);
        EditScreen editScreen(font, theme);

        AppScreen currentScreen = AppScreen::MENU;

        while (window.isOpen()) {
            sf::Event event;
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (currentScreen == AppScreen::MENU &&
                    event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                    menu.handleClick(mousePos, currentScreen, window);
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (currentScreen == AppScreen::ADD_PHONE)
                        addScreen.handleBack(mousePos, currentScreen);
                    else if (currentScreen == AppScreen::DISPLAY_LIST)
                        displayScreen.handleBack(mousePos, currentScreen);
                    else if (currentScreen == AppScreen::SEARCH_PHONE)
                        searchScreen.handleBack(mousePos, currentScreen);
                    else if (currentScreen == AppScreen::DELETE_PHONE)
                        deleteScreen.handleBack(mousePos, currentScreen);
                    else if (currentScreen == AppScreen::EDIT_PHONE)
                        editScreen.handleBack(mousePos, currentScreen);
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    currentScreen = AppScreen::MENU;
                }
            }

            window.clear();
            window.draw(bgSprite);

            if (currentScreen == AppScreen::MENU) {
                menu.update(mousePos);
                menu.draw(window);
            }
            else if (currentScreen == AppScreen::ADD_PHONE) {
                addScreen.draw(window, font);
            }
            else if (currentScreen == AppScreen::DISPLAY_LIST) {
                displayScreen.draw(window, font);
            }
            else if (currentScreen == AppScreen::SEARCH_PHONE) {
                searchScreen.draw(window, font);
            }
            else if (currentScreen == AppScreen::DELETE_PHONE) {
                deleteScreen.draw(window, font);
            }
            else if (currentScreen == AppScreen::EDIT_PHONE) {
                editScreen.draw(window, font);
            }

            window.display();
        }

        return 0;
    }