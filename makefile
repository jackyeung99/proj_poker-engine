# Compiler
CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) -Wall -std=c++17

# Directories
SRC_DIR = src
GAME_DIR = $(SRC_DIR)/game
PLAYER_DIR = $(SRC_DIR)/players
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# Source files
SRCS_SRC = $(wildcard $(SRC_DIR)/*.cpp)
SRCS_GAME = $(wildcard $(GAME_DIR)/*.cpp)
SRCS_PLAYER = $(wildcard $(PLAYER_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS_SRC))
OBJS += $(patsubst $(GAME_DIR)/%.cpp, $(BUILD_DIR)/game/%.o, $(SRCS_GAME))
OBJS += $(patsubst $(PLAYER_DIR)/%.cpp, $(BUILD_DIR)/player/%.o, $(SRCS_PLAYER))

# Output Executable
TARGET = $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Build rules
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/game/%.o: $(GAME_DIR)/%.cpp | $(BUILD_DIR)/game
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/player/%.o: $(PLAYER_DIR)/%.cpp | $(BUILD_DIR)/player
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure directories
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/game:
	mkdir -p $(BUILD_DIR)/game

$(BUILD_DIR)/player:
	mkdir -p $(BUILD_DIR)/player

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Run
run: all
	./$(TARGET)

.PHONY: all clean run
