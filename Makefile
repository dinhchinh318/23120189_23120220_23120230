CXX      := g++-13
CXXFLAGS := -std=c++2b -g -I source
LDFLAGS  := -lboost_locale -lodbc

SRC      := $(wildcard source/*.cpp)
OBJ      := $(SRC:source/%.cpp=build/%.o)
TARGET   := release/out

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

build/%.o: source/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build release/out
