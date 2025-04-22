CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./source/include

SRC_DIR = source/src
LIB_DIR = source/lib
INC_DIR = source/include
OUT_DIR = release
TARGET = $(OUT_DIR)/out

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(LIB_DIR)/*.cpp) source/main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
