# Tên chương trình
TARGET := build/PhoneManagement.exe

# Trình biên dịch
CXX := g++
CXXFLAGS := -I./SFML/include -std=c++17
LDFLAGS := -mconsole -L./SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lodbc32

# Tìm tất cả các file .cpp trong thư mục source và các thư mục con
SRC := $(wildcard source/*.cpp) $(wildcard source/**/*.cpp)

# Danh sách file .o tương ứng trong thư mục build
OBJ := $(patsubst source/%.cpp, build/%.o, $(SRC))

# Mặc định build
all: $(TARGET)

# Liên kết file object thành file thực thi (build/app.exe)
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Biên dịch từng file .cpp thành .o trong thư mục build
build/%.o: source/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean: xóa toàn bộ nội dung trong thư mục build
clean:
	@if exist build rmdir /S /Q build

.PHONY: all clean
