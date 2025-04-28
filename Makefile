SRC = $(wildcard source/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = PhoneManagement

# ⚡ Bổ sung dòng này:
CXXFLAGS = -I./SFML/include

all: $(TARGET)

# Compile từng file .cpp thành file .o
%.o: %.cpp
	g++ -c $< -o $@ $(CXXFLAGS)

# Link tất cả .o thành chương trình
$(TARGET): $(OBJ)
	g++ $(OBJ) -o $(TARGET) -L./SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	del /Q $(OBJ) $(TARGET).exe
