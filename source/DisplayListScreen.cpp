#include "DisplayListScreen.h"

void DisplayListScreen::draw(sf::RenderWindow& window, sf::Font& font) 
{
    window.draw(title);
    drawBackButton(window);

    float y = 190;  // vị trí y bắt đầu để in danh sách
    for (const auto& phone : phones) {
        std::stringstream ss;
        ss << "ID: " << phone.getID()
            << " | Name: " << phone.getName()
            << " | Manu: " << phone.getManu()
            << " | Price: " << phone.getPrice()
            << " | OS: " << phone.getConfig().operatingSystem
            << " | RAM: " << phone.getConfig().ram << "GB"
            << " | ROM: " << phone.getConfig().rom << "GB"
            << " | Screen: " << phone.getConfig().screenSize << "\""
            << " | Pin: " << phone.getConfig().pin << "mAh";

        sf::Text line(ss.str(), font, 15);
        line.setFillColor(sf::Color::Black);
        line.setPosition(75, y);
        y += 30;
        window.draw(line);
    }
}