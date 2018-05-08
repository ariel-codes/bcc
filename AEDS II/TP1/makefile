CC=gcc
CFLAGS=-Wall -std=c99 -Wextra -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wconversion
LIBS=-lm
BIN=tp1

FILES=$(wildcard *.c)

all: $(FILES)
	gcc -o $@ $^ $(CFLAGS) $(LIBS) -o $(BIN)

run: $(FILES)
	gcc -o $@ $^ $(CFLAGS) $(LIBS) -o $(BIN)
	./$(BIN)

clean:
	rm