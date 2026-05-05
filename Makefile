APP := while_true_colony
CXX ?= g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Wpedantic -O0
INCLUDE_DIR := include
OBJ_DIR := obj
SRC := $(shell find src -name '*.cpp')
OBJ := $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)
BIN := bin/$(APP)

UNAME_S := $(shell uname -s)
GLFW_CFLAGS := $(shell pkg-config --cflags glfw3 2>/dev/null)
GLFW_LIBS := $(shell pkg-config --libs glfw3 2>/dev/null)

OPENGL_LIBS := -lGL

LDFLAGS := $(GLFW_LIBS) $(OPENGL_LIBS)

.PHONY: all run clean fclean re

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p bin
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $(GLFW_CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf bin

re: fclean all
