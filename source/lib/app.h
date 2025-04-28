#ifndef _APP_H_
#define _APP_H_

#include "../include/QuanLyDienThoai.h"
#include "../include/utils.h"

#ifdef _WIN32
    #include <windows.h>
    inline void GotoXY(int x, int y) {
        COORD coord = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    inline void SetColor(int background_color, int text_color) {
        int color_code = background_color * 16 + text_color;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_code);
    }
#else
    #include <iostream>

    inline void GotoXY(int x, int y) {
        cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
    }

    inline void SetColor(int background_color, int text_color) {
        cout << "\033[" << (background_color + 40) << ";" << (text_color + 30) << "m";
    }
#endif

void runApp();

#endif