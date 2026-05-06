APP := while_true_colony
CXX ?= g++
CC ?= gcc
# SANITIZE_FLAGS := -fsanitize=address
CXXFLAGS := -std=c++23 -Wall -Wextra -Wpedantic -O0 -MMD -MP $(SANITIZE_FLAGS)
CXXFLAGS += -g3
CCFLAGS := -Wall -Wextra -Wpedantic -O0 -MMD -MP
CCFLAGS += -g3
INCLUDE_DIR := include
THIRD_PARTY_DIR := third_party
GLAD_DIR := $(THIRD_PARTY_DIR)/glad
OBJ_DIR := obj
SRC_CPP := $(shell find src -name '*.cpp')
SRC_C := $(shell find $(GLAD_DIR)/src -name '*.c' 2>/dev/null)
OBJ_CPP := $(SRC_CPP:src/%.cpp=$(OBJ_DIR)/src/%.o)
OBJ_C := $(SRC_C:$(GLAD_DIR)/src/%.c=$(OBJ_DIR)/third_party/glad/src/%.o)
OBJ := $(OBJ_CPP) $(OBJ_C)
DEP := $(OBJ:.o=.d)
BIN := bin/$(APP)
FORMAT_FILES := $(shell find include src $(GLAD_DIR) -type f 2>/dev/null)

UNAME_S := $(shell uname -s)
GLFW_CFLAGS := $(shell pkg-config --cflags glfw3 2>/dev/null)
GLFW_LIBS := $(shell pkg-config --libs glfw3 2>/dev/null)

OPENGL_LIBS := -lGL

LDFLAGS := $(SANITIZE_FLAGS) $(GLFW_LIBS) $(OPENGL_LIBS)

.PHONY: all run clean fclean re format

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p bin
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ_DIR)/src/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -I$(GLAD_DIR)/include $(GLFW_CFLAGS) -c $< -o $@

$(OBJ_DIR)/third_party/glad/src/%.o: $(GLAD_DIR)/src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -I$(GLAD_DIR)/include -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf bin

re: fclean all

format:
	clang-format -i $(FORMAT_FILES)

-include $(DEP)
