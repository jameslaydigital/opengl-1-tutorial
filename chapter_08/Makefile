# Makefile for Chapter 8
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    CFLAGS += -Wno-deprecated-declarations
    LDFLAGS = -framework OpenGL -framework GLUT
else
    LDFLAGS = -lGL -lGLU -lglut -lm
endif

TARGET = demo
SOURCES = main.c materials.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

