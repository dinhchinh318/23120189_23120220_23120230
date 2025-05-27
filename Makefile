# --------------------------
# TÊN CHƯƠNG TRÌNH CHÍNH
TARGET := release/PhoneManagement.exe
TEST_TARGET := release/test_app.exe

# --------------------------
# TRÌNH BIÊN DỊCH & CỜ BIÊN DỊCH
CXX := g++
CXXFLAGS := -I./SFML/include -I./source -std=c++17
LDFLAGS := -mconsole -L./SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lodbc32

# --------------------------
# NGUỒN CHƯƠNG TRÌNH CHÍNH
SRC := $(wildcard source/*.cpp) $(wildcard source/**/*.cpp)
OBJ := $(patsubst source/%.cpp, release/%.o, $(SRC))

# --------------------------
# NGUỒN TEST
TEST_SRC := $(wildcard tests/*.cpp)
GTEST_SRC := googletest/googletest/src/gtest-all.cc
GTEST_MAIN_SRC := googletest/googletest/src/gtest_main.cc
TEST_OBJ := $(patsubst tests/%.cpp, release/tests/%.o, $(TEST_SRC)) release/gtest-all.o release/gtest_main.o

# --------------------------
# MẶC ĐỊNH
all: $(TARGET)

# --------------------------
# BIÊN DỊCH CHƯƠNG TRÌNH CHÍNH
$(TARGET): $(OBJ)
	@if not exist release mkdir release
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

release/%.o: source/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --------------------------
# BUILD & RUN TEST
test: $(TEST_TARGET)
	@echo "====== Running Unit Tests ======"
	@$(TEST_TARGET)

TEST_DEP_OBJ := \
    release/PhoneManagement/PhoneManagement.o \
    release/PhoneManagement/Phone.o \
    release/FunctionScreen/addScreen_utils.o \
    release/FunctionScreen/delScreen_utils.o \
    release/FunctionScreen/edit_exec_utils.o \
    release/FunctionScreen/searchScreen_utils.o

$(TEST_TARGET): $(TEST_OBJ) $(TEST_DEP_OBJ)
	@if not exist release mkdir release
	$(CXX) $^ -o $@ $(LDFLAGS)

release/tests/%.o: tests/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) -Igoogletest/googletest/include -Igoogletest/googletest $(CXXFLAGS) -c $< -o $@

release/gtest-all.o: googletest/googletest/src/gtest-all.cc
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) -Igoogletest/googletest/include -Igoogletest/googletest $(CXXFLAGS) -c $< -o $@

release/gtest_main.o: googletest/googletest/src/gtest_main.cc
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) -Igoogletest/googletest/include -Igoogletest/googletest $(CXXFLAGS) -c $< -o $@

# --------------------------
# CLEAN
clean:
	@if exist release rmdir /S /Q release

.PHONY: all clean test
