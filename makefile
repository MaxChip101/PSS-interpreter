# Define compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SRCS = ./src/main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = pss

# Default target
all:
	mkdir -p ./bin
	$(CXX) $(SRCS) -o ./bin/$(TARGET)

# Clean command to remove generated files
clean:
	rm -rf ./bin