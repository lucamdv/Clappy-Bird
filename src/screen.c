#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "game.h"

// Limpa a tela do terminal
void clear_screen() {
    system("clear");
}

// Renderiza o jogo na tela
void render_game() {
    clear_screen();  // Limpar a tela antes de desenhar

    // Desenhar a moldura
    for (int x = 0; x < WIDTH + 2; x++) printf("-");
    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("|");  // Início da linha da moldura

        for (int x = 0; x < WIDTH; x++) {
            if (y == player.y && x == player.x) {
                printf("🐔");  // Galinha
            } else {
                int is_car = 0;
                for (int i = 0; i < TOTAL_ROADS; i++) {
                    if (y == cars[i].y && x == cars[i].x) {
                        printf("🚗");  // Carro
                        is_car = 1;
                        break;
                    }
                }
                if (!is_car) {
                    if (y % (ROAD_HEIGHT + 1) == 0) {
                        printf("██");  // Calçada
                    } else {
                        printf("  ");  // Rua
                    }
                }
            }
        }
        printf("|\n");
    }

    for (int x = 0; x < WIDTH + 2; x++) printf("-");
    printf("\n");
}
