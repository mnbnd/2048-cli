# Makefile to compile the 2048 CLI game

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Target executable
TARGET = game

# Source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJS)
$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp board.h Node.h
$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
rm -f $(TARGET) $(OBJS)

