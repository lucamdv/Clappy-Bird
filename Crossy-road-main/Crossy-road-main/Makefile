CC = gcc
CFLAGS = -Iinclude
SRC_FILES = src/main.c src/game.c src/input.c src/screen.c src/keyboard.c src/timer.c src/menu.c
OBJ_FILES = $(SRC_FILES:src/%.c=build/%.o)
TARGET = crossy_road

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) -o $(TARGET) $(OBJ_FILES)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/*.o $(TARGET)
