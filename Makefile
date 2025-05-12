# Danh sách các file nguồn
SRC := $(wildcard source/*.cpp) 

# Tạo danh sách file .o tương ứng
OBJ := $(patsubst source/%.cpp, build/%.o, $(SRC))

# Tên chương trình
TARGET := app

# Cờ biên dịch
CXX := g++
CXXFLAGS := -I./SFML/include -std=c++17

# Thư viện liên kết (đã thêm -lodbc)
LDFLAGS := -L./SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lodbc32

# Mặc định build tất cả
all: $(TARGET)

# Tạo thư mục build nếu chưa có
build:
	mkdir -p build

# Build chương trình
$(TARGET): build $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Compile từng file .cpp thành .o
build/%.o: source/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Dọn file tạm
clean:
	del /Q build\*.o $(TARGET).exe

.PHONY: all clean