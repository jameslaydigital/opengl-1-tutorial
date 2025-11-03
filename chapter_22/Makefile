CC=gcc
CFLAGS=-Wall -std=c99 -O2
UNAME_S:=$(shell uname -s)
ifeq ($(UNAME_S),Darwin)
CFLAGS+=-Wno-deprecated-declarations
LDFLAGS=-framework OpenGL -framework GLUT
else
LDFLAGS=-lGL -lGLU -lglut -lm
endif
game: game.c
	$(CC) $(CFLAGS) game.c -o game $(LDFLAGS)
clean:
	rm -f game
run: game
	./game
.PHONY: clean run

