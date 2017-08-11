CC=gcc
CFLAGS=-Wall -pedantic 
LIBS=-lm

DEPS = src/funcGrafos.h
SRC = src/main.c src/funcGrafos.c
grafo: $(DEPS) $(SRC)
	gcc -o grafo $(SRC) $(CFLAGS) $(LIBS)
