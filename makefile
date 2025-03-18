# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++17
LDFLAGS = 

# Source and Object files
# SRC = src/mylib.cpp
# OBJ = $(SRC:.cpp=.o)

# Output binaries
BIN = bin
EXECUTABLES = $(BIN)/main

# Default target (build all executables)
all: $(EXECUTABLES)

# Rule for main1
$(BIN)/main: src/hand.cpp $(OBJ)
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $^ -o $@


# Compile object files for shared library
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BIN)/* $(OBJ)
