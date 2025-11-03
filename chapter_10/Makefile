CC=gcc
CFLAGS=-Wall -std=c99 -O2
UNAME_S:=$(shell uname -s)
ifeq ($(UNAME_S),Darwin)
CFLAGS+=-Wno-deprecated-declarations
LDFLAGS=-framework OpenGL -framework GLUT
else
LDFLAGS=-lGL -lGLU -lglut -lm
endif
demo: main.c
	$(CC) $(CFLAGS) main.c -o demo $(LDFLAGS)
clean:
	rm -f demo
.PHONY: clean

