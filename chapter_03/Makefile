# Advanced Makefile for Chapter 3: Project Skeleton
# Supports automatic dependency generation, debug/release builds

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -pedantic

# Debug vs Release
ifdef DEBUG
    CFLAGS += -g -O0 -DDEBUG
    BUILD_TYPE = debug
else
    CFLAGS += -O2 -DNDEBUG
    BUILD_TYPE = release
endif

# Platform detection
UNAME_S := $(shell uname -s)

# macOS: Suppress OpenGL deprecation warnings
ifeq ($(UNAME_S),Darwin)
    CFLAGS += -Wno-deprecated-declarations
    LDFLAGS = -framework OpenGL -framework GLUT
else
    LDFLAGS = -lGL -lGLU -lglut -lm
endif

# Target executable
TARGET = demo

# Source files
SOURCES = main.c render.c gl_utils.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Dependency files
DEPS = $(OBJECTS:.o=.d)

# Default target
all: $(TARGET)
	@echo "Build complete ($(BUILD_TYPE)): ./$(TARGET)"

# Link the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile with automatic dependency generation
%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)
	@echo "Clean complete"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build
debug:
	@$(MAKE) DEBUG=1

# Release build
release:
	@$(MAKE)

# Show build configuration
info:
	@echo "Build Configuration:"
	@echo "  Platform:   $(UNAME_S)"
	@echo "  Build Type: $(BUILD_TYPE)"
	@echo "  CC:         $(CC)"
	@echo "  CFLAGS:     $(CFLAGS)"
	@echo "  LDFLAGS:    $(LDFLAGS)"
	@echo "  Sources:    $(SOURCES)"
	@echo "  Objects:    $(OBJECTS)"

# Phony targets
.PHONY: all clean run debug release info

