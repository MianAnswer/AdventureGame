# Directories
SRC_DIR := src
BIN_DIR := bin
INC_DIR := include

# Compiler and flags
CXX := g++
CXXFLAGS := -I$(INC_DIR) -Wall -Wextra -std=c++17

# Find all .cpp files recursively in SRC_DIR
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Map source files to object files in BIN_DIR, preserving subdirectory structure
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRCS))

# Target executable
TARGET := $(BIN_DIR)/AdventureGame

# Default rule
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files to object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | prepare_dirs
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create necessary bin subdirectories
prepare_dirs:
	@mkdir -p $(BIN_DIR)
	@for dir in $(shell find $(SRC_DIR) -type d); do \
		mkdir -p $(BIN_DIR)/$${dir#$(SRC_DIR)/}; \
	done

# Clean build files
clean:
	rm -rf $(BIN_DIR)/*

.PHONY: all clean prepare_dirs