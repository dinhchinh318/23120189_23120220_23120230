#ifndef _WINDOWS_H_
#define _WINDOWS_H_

#define _CRT_SECURE_NO_WARNINGS
#include "QuanLyDienThoai.h"


void GotoXY(int x, int y);
void SetColor(int backgound_color, int text_color);
void readDataFile(QuanLyDienThoai& list, const char* filename);
#endif