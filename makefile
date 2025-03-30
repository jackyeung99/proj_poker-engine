# Compiler
CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) -Wall -std=c++17

# Directories
SRC_DIR = src
GAME_DIR = $(SRC_DIR)/game
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# Find all source files in src/ and src/game/
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(GAME_DIR)/*.cpp)

# Convert source files into corresponding object files in build/
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
OBJS := $(patsubst $(GAME_DIR)/%.cpp, $(BUILD_DIR)/game/%.o, $(OBJS))

# Output Executable
TARGET = $(BIN_DIR)/main

# Default target: Build everything
all: $(TARGET)

# Compile and link executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile source files into object files (src/*.cpp -> build/*.o)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile game source files into object files (src/game/*.cpp -> build/game/*.o)
$(BUILD_DIR)/game/%.o: $(GAME_DIR)/%.cpp | $(BUILD_DIR)/game
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure bin and build directories exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/game:
	mkdir -p $(BUILD_DIR)/game

# Clean up compiled files
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/game/*.o $(TARGET)

# Run the program
run: all
	./$(TARGET)