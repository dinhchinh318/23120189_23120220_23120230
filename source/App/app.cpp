#include "app.h"

void giaodien() 
{
    sf::RenderWindow window(sf::VideoMode(1500, 800), "Phone Management", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("Fonts/ARIAL.ttf")) {
        std::cerr << "Can't find font!" << std::endl;
        return;
    }

    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    if (!bgTexture.loadFromFile("Pictures/background.jpg")) {
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

    UITheme theme;
    MenuScreen menu(font, theme);
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
            menu.draw(window, font);
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
}

void run()
{
    SQLHENV hEnv;
    SQLHDBC hDbc;

    if (!connectToSQL(hEnv, hDbc)) {
        //return -1;
        return;
    }

    PhoneManagement pMan;
    int choice;
    do {
        cout << "\n=== PHONE MANAGEMENT MENU ===\n";
        cout << "1. Add phone\n";
        cout << "2. Display phone list\n";
        cout << "3. Search by name\n";
        cout << "4. Delete by ID\n";
        cout << "5. Edit phone information\n";
        cout << "0. Exit\n";
        cout << "Select an option: ";
        cin >> choice;

        if (choice == 1)
        {
            Phone phoneTemp;

            /*int id = nhapSoNguyen("Nhap ID dien thoai: ");
            dtTemp.setID(id);*/

            phoneTemp.insertValue();       // Nhập các thông tin còn lại
            phoneTemp.insertToDB(hDbc);   // Lưu vào CSDL
        }
        else if (choice == 2)
        {
            // cout << ql << endl;

            pMan.getPhoneList(hDbc);  // Gọi hàm lấy danh sách điện thoại từ CSDL
            cout << pMan << endl;

            //ql.XuatDanhSachDienThoai(hDbc);  // Gọi hàm xuất danh sách điện thoại
            // cout << "helooo";

            // cout << ql << endl;
            // ql.XuatDanhSachDienThoai(hDbc);  // Gọi hàm xuất danh sách điện thoại
        }
        else if (choice == 3)
        {
            string key;
            cout << "Enter name or ID to search: ";
            cin.ignore(); // Loại bỏ ký tự '\n' còn lại trong bộ đệm
            getline(cin, key);  // Nhập tên hoặc ID cần tìm

            // Kiểm tra xem key có phải là một số không (ID)
            bool isNumber = !key.empty() && all_of(key.begin(), key.end(), ::isdigit);

            Phone* p = nullptr;  // Khởi tạo con trỏ

            // Nếu key là số, tìm theo ID
            if (isNumber) {
                int id = stoi(key);  // Chuyển key sang số nguyên (ID)
                p = pMan.findByID(hDbc, id);  // Gọi hàm tìm kiếm theo ID
            }
            else {
                // Nếu key không phải số, tìm theo tên
                p = pMan.findByName(hDbc, key);  // Gọi hàm tìm kiếm theo tên
            }

            if (p != nullptr && p->getID() != 0) {  // Kiểm tra nếu điện thoại tìm thấy
                cout << "Phone found:\n" << *p << endl;  // In đối tượng DienThoai
            }
            else {
                cout << "No phone found with name or ID: " << key << endl;
            }
        }
        else if (choice == 4)
        {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            pMan.removePhoneByID(hDbc, id);  // Gọi hàm xóa theo ID
        }
        else if (choice == 5)
        {
            int id;
            cout << "Enter ID to edit: ";
            cin >> id;
            Phone* p = pMan.findByID(hDbc, id);  // Tìm điện thoại theo ID
            if (p != nullptr && p->getID() != 0) {  // Kiểm tra nếu điện thoại tìm thấy
                cout << "Phone found:\n" << *p << endl;  // In đối tượng DienThoai
                // Nhập thông tin mới
                cout << "Enter new information:\n";
                /*dt->nhapDuLieu();*/
                // Chỉnh sửa thông tin trong CSDL
                pMan.editPhoneInfor(hDbc, id);  // Gọi hàm chỉnh sửa thông tin
            }
            else {
                cout << "No phone found with ID: " << id << endl;
            }
        }
    } while (choice != 0);
}