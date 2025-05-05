#ifndef _LIB_SRC_H_
#define _LIB_SRC_H_

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <thread>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <windows.h>
#include <sqlext.h>// SQL Server ODBC header
// #include <io.h>
// #include <fcntl.h> 
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostream;
using std::out_of_range;
using std::forward_iterator_tag;

string ChuanHoaGia(string& gia);
int nhapSoNguyen(const std::string& thongBao);
bool connectToSQL(SQLHENV& hEnv, SQLHDBC& hDbc);
#endif