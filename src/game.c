#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "keyboard.h"
#include "screen.h"
#include "timer.h"

Player player;
Car cars[TOTAL_ROADS];
int game_over = 0;

void init_game() {
    player.x = WIDTH / 2;
    player.y = HEIGHT - 2;

    for (int i = 0; i < TOTAL_ROADS; i++) {
        cars[i].y = i * (ROAD_HEIGHT + 1) + 1;
        cars[i].x = rand() % (WIDTH - 2 * SIDEWALK_WIDTH) + SIDEWALK_WIDTH;
        cars[i].direction = (rand() % 2) == 0 ? 1 : -1;
    }
}

void update() {
    for (int i = 0; i < TOTAL_ROADS; i++) {
        cars[i].x += cars[i].direction;
        if (cars[i].x >= WIDTH - SIDEWALK_WIDTH) {
            cars[i].x = WIDTH - SIDEWALK_WIDTH - 1;
            cars[i].direction = -1;
        } else if (cars[i].x < SIDEWALK_WIDTH) {
            cars[i].x = SIDEWALK_WIDTH;
            cars[i].direction = 1;
        }
    }

    for (int i = 0; i < TOTAL_ROADS; i++) {
        if (cars[i].y == player.y && player.x >= cars[i].x - 1 && player.x <= cars[i].x + 1) {
            game_over = 1;
        }
    }

    if (player.y <= 1) {
        player.y = HEIGHT - 2;
        for (int i = 0; i < TOTAL_ROADS; i++) {
            cars[i].y += ROAD_HEIGHT + 1;
            if (cars[i].y >= HEIGHT - 1) {
                cars[i].y = 1;
                cars[i].x = rand() % (WIDTH - 2 * SIDEWALK_WIDTH) + SIDEWALK_WIDTH;
            }
        }
    }
}

int play_game() {
    srand(time(NULL));
    init_game();
    long last_frame_time = get_time();
    while (!game_over) {
        long current_time = get_time();
        if (current_time - last_frame_time >= 200) {
            char input = get_keypress();
            handle_input(input);
            update();
            render_game();
            last_frame_time = current_time;
        }
        delay(16);  // Delay de 16ms para limitar a 60 FPS
    }
    printf("Game Over!\n");
    return 0;
}
