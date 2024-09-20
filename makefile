# Compiler
CXX = g++

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Executable name
EXEC = pss

# Flags
CXXFLAGS = -Wall -std=c++17

# Default rule
all: $(BUILD_DIR)/$(EXEC)

# Compile all source files directly into the final executable
$(BUILD_DIR)/$(EXEC): $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

# Clean up the build directory
clean:
	rm -rf $(BUILD_DIR)/$(EXEC)

# Make sure nothing else runs if the Makefile targets are up-to-date
.PHONY: all clean
