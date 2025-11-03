# Makefile for Chapter 2: Hello Window
# Works on Linux and macOS

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2

# macOS: Suppress OpenGL deprecation warnings
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    CFLAGS += -Wno-deprecated-declarations
endif

# Linker flags
LDFLAGS = -lGL -lGLU -lglut

# macOS uses different framework paths
ifeq ($(UNAME_S),Darwin)
    LDFLAGS = -framework OpenGL -framework GLUT
endif

# Target executable
TARGET = demo

# Source files
SOURCES = main.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete! Run with: ./$(TARGET)"

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run

