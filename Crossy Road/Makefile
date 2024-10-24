CC = gcc
CFLAGS = -Iinclude
OBJ = src/main.o src/game.o src/input.o

all: crossy_road

crossy_road: $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o crossy_road
