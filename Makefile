CC = gcc
CFLAGS = -Iinclude
SRC = src/main.c src/game.c src/input.c src/screen.c src/keyboard.c src/timer.c
OBJ = build/main.o build/game.o build/input.o build/screen.o build/keyboard.o build/timer.o

# Cria o executável
all: crossy_road

crossy_road: $(OBJ)
	$(CC) -o $@ $^

# Regras para compilar os arquivos de origem
build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*.o crossy_road
