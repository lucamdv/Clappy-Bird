#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "game.h"
#include "input.h"

// Definição da galinha e dos carros
Player player;
Car cars[TOTAL_ROADS]; // Um carro para cada rua
int game_over = 0;

// Função para inicializar o jogo
void init_game() {
    player.x = WIDTH / 2; // Posição inicial da galinha
    player.y = HEIGHT - 2; // Posição inicial da galinha

    // Inicializa carros com uma posição aleatória em cada rua
    for (int i = 0; i < TOTAL_ROADS; i++) {
        cars[i].y = i * (ROAD_HEIGHT + 1) + 1; // Posição fixa para cada rua
        cars[i].x = rand() % (WIDTH - 2 * SIDEWALK_WIDTH) + SIDEWALK_WIDTH; // Posição aleatória dentro da rua
        cars[i].direction = (rand() % 2) == 0 ? 1 : -1; // Direção aleatória
    }
}

// Função para desenhar o jogo
void draw() {
    system("clear"); // Limpa a tela

    // Desenha a moldura
    for (int x = 0; x < WIDTH + 2; x++) printf("-");
    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("|"); // Início da linha da moldura

        for (int x = 0; x < WIDTH; x++) {
            // Desenha a galinha
            if (y == player.y && x == player.x) {
                printf("🐔"); // Galinha
            } else {
                int is_car = 0;
                // Desenha os carros
                for (int i = 0; i < TOTAL_ROADS; i++) {
                    if (y == cars[i].y && x == cars[i].x) {
                        printf("🚗"); // Carro
                        is_car = 1;
                        break;
                    }
                }
                // Desenha calçadas e ruas
                if (y % (ROAD_HEIGHT + 1) == 0) { // Linha da calçada
                    printf("██"); // Calçada
                } else if (y % (ROAD_HEIGHT + 1) == 1) { // Linha da rua
                    if (x < SIDEWALK_WIDTH || x >= WIDTH - SIDEWALK_WIDTH) {
                        printf("██"); // Calçada
                    } else {
                        printf("  "); // Espaço em branco (rua)
                    }
                } else {
                    printf("  "); // Espaço em branco
                }
            }
        }

        printf("|\n"); // Final da linha da moldura
    }

    for (int x = 0; x < WIDTH + 2; x++) printf("-");
    printf("\n");
}

// Função para atualizar a lógica do jogo
void update() {
    // Mover carros
    for (int i = 0; i < TOTAL_ROADS; i++) {
        cars[i].x += cars[i].direction;

        // Inverter direção ao atingir a borda
        if (cars[i].x >= WIDTH - SIDEWALK_WIDTH) {
            cars[i].x = WIDTH - SIDEWALK_WIDTH - 1;
            cars[i].direction = -1; // Mover para a esquerda
        } else if (cars[i].x < SIDEWALK_WIDTH) {
            cars[i].x = SIDEWALK_WIDTH;
            cars[i].direction = 1; // Mover para a direita
        }
    }

    // Verificar colisão com hitbox horizontal ajustada
    for (int i = 0; i < TOTAL_ROADS; i++) {
        if (cars[i].y == player.y) {
            if (player.x >= cars[i].x - 1 && player.x <= cars[i].x + 1) {
                // A colisão acontece se a galinha estiver dentro do intervalo horizontal do carro
                game_over = 1;
            }
        }
    }

    // Gerar novas ruas
    if (player.y <= 1) { // Quando a galinha chegar ao topo
        player.y = HEIGHT - 2; // Reinicia a posição da galinha
        for (int i = 0; i < TOTAL_ROADS; i++) {
            cars[i].y += ROAD_HEIGHT + 1; // Move as ruas para cima
            if (cars[i].y >= HEIGHT - 1) {
                cars[i].y = 1; // Reinicia a posição do carro
                cars[i].x = rand() % (WIDTH - 2 * SIDEWALK_WIDTH) + SIDEWALK_WIDTH; // Nova posição aleatória
            }
        }
    }
}

// Função principal do jogo
int play_game() {
    srand(time(NULL));
    init_game();
    while (!game_over) {
        draw();
        char input = get_char_non_blocking();
        if (input == 'w' && player.y > 1) player.y--; // Mover para cima
        if (input == 's' && player.y < HEIGHT - 2) player.y++; // Mover para baixo
        if (input == 'a' && player.x > SIDEWALK_WIDTH) player.x--; // Mover para esquerda
        if (input == 'd' && player.x < WIDTH - SIDEWALK_WIDTH - 1) player.x++; // Mover para direita
        update();
        usleep(200000); // Atraso para controle de velocidade
    }
    printf("Game Over!\n");
    return 0;
}
