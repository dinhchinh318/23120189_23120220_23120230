# Tên chương trình
TARGET := app

# Trình biên dịch
CXX := g++
CXXFLAGS := -I./SFML/include -std=c++17
LDFLAGS := -L./SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lodbc32

# Tìm tất cả các file .cpp
SRC := $(wildcard source/**/*.cpp)

# Tạo danh sách object file trong build/, không có thư mục con
OBJ := $(addprefix build/, $(notdir $(SRC:.cpp=.o)))


# Mặc định build
all: $(TARGET)

# Biên dịch chương trình
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) 

# Biên dịch từng file cpp thành .o trong build/
build/%.o:
	$(CXX) -c $(foreach src,$(SRC),$(if $(findstring /$*.cpp,$(src)),$(src))) -o $@ $(CXXFLAGS)

# Clean
clean:
	del /Q build\*.o $(TARGET).exe

.PHONY: all clean
