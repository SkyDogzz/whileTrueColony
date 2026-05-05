APP := while_true_colony
CXX ?= g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Wpedantic -O0
SRC := src/main.cpp
BIN := bin/$(APP)

UNAME_S := $(shell uname -s)
GLFW_CFLAGS := $(shell pkg-config --cflags glfw3 2>/dev/null)
GLFW_LIBS := $(shell pkg-config --libs glfw3 2>/dev/null)

OPENGL_LIBS := -lGL

LDFLAGS := $(GLFW_LIBS) $(OPENGL_LIBS)

.PHONY: all run clean

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(GLFW_CFLAGS) $< -o $@ $(LDFLAGS)

run: $(BIN)
	./$(BIN)

clean:
	rm -rf bin
