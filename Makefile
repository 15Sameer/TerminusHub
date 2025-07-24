CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude
LDFLAGS = -lncurses

SRCS = \
    src/main.cpp \
    src/snake.cpp \
    src/tetris.cpp \
    src/tictactoe.cpp \
    src/hangman.cpp \
    src/echoes.cpp

OBJS = $(SRCS:src/%.cpp=build/%.o)
TARGET = terminus

all: $(TARGET)

# Compile source files into object files
build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -rf build $(TARGET)

.PHONY: all clean
