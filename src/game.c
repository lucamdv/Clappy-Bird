#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "keyboard.h"
#include "screen.h"
#include "timer.h"

Player player;
Car cars[TOTAL_ROADS];

int game_over = 0;
int score = 0; // Inicializa a pontuação
int last_road_index = -1; // Índice da última rua atravessada

HighScoreEntry high_scores[MAX_SCORES];

void save_high_scores() {
    FILE *file = fopen("highscores.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < MAX_SCORES; i++) {
            fprintf(file, "%s %d\n", high_scores[i].name, high_scores[i].score);
        }
        fclose(file);
    }
}

void load_high_scores() {
    FILE *file = fopen("highscores.txt", "r");
    if (file != NULL) {
        for (int i = 0; i < MAX_SCORES; i++) {
            fscanf(file, "%s %d", high_scores[i].name, &high_scores[i].score);
        }
        fclose(file);
    }
}

void update_high_scores(const char *player_name, int new_score) {
    for (int i = 0; i < MAX_SCORES; i++) {
        if (new_score > high_scores[i].score) {
            for (int j = MAX_SCORES - 1; j > i; j--) {
                high_scores[j] = high_scores[j - 1]; // Desloca os scores
            }
            strncpy(high_scores[i].name, player_name, sizeof(high_scores[i].name));
            high_scores[i].score = new_score;
            break;
        }
    }
}

void show_high_scores() {
    printf("\nTabela de Recordes:\n");
    printf("--------------------\n");
    for (int i = 0; i < MAX_SCORES; i++) {
        printf("%d. %s - %d\n", i + 1, high_scores[i].name, high_scores[i].score);
    }
    printf("--------------------\n");
    printf("Pressione Enter para voltar ao menu.\n");
    while (get_keypress() != 10); // Espera até que Enter seja pressionado
}

void init_game() {
    player.x = WIDTH / 2;
    player.y = HEIGHT - 2;
    score = 0; // Reseta a pontuação ao iniciar o jogo
    last_road_index = -1; // Reinicia o índice da última rua

    // Configuração de carros para dificuldade
    for (int i = 0; i < TOTAL_ROADS; i++) {
        cars[i].y = i * (ROAD_HEIGHT + 1) + 1;

        if (difficulty == 3) { // Dificuldade difícil
            // Gera carros em posições adequadas
            cars[i].x = rand() % (WIDTH - 2 * SIDEWALK_WIDTH - 6) + SIDEWALK_WIDTH; // Espaço para 3 carros
        } else {
            cars[i].x = rand() % (WIDTH - 2 * SIDEWALK_WIDTH) + SIDEWALK_WIDTH;
        }
        cars[i].direction = (rand() % 2) == 0 ? 1 : -1;
    }
}

void update() {
    // Atualiza a posição dos carros
    for (int i = 0; i < TOTAL_ROADS; i++) {
        cars[i].x += cars[i].direction;
        
        // Verifica os limites da tela
        if (cars[i].x >= WIDTH - SIDEWALK_WIDTH) {
            cars[i].x = WIDTH - SIDEWALK_WIDTH - 1;
            cars[i].direction = -1;
        } else if (cars[i].x < SIDEWALK_WIDTH) {
            cars[i].x = SIDEWALK_WIDTH;
            cars[i].direction = 1;
        }
    }

    // Verifica colisão com todos os carros
    for (int i = 0; i < TOTAL_ROADS; i++) {
        // Verifica se a galinha está na mesma linha que o carro
        if (cars[i].y == player.y) {
            // Verifica as posições de colisão, considerando o terceiro carro
            if (player.x >= cars[i].x - 1 && player.x <= cars[i].x + 6) { // Considera deslocamento para 3 carros
                game_over = 1; // Colisão com carro
                break; // Para verificar a colisão uma vez
            }
        }
    }

    // Verifica em qual rua o jogador está
    int current_road_index = player.y / (ROAD_HEIGHT + 1);
    
    // Se o jogador moveu para uma nova rua
    if (current_road_index < TOTAL_ROADS && current_road_index != last_road_index) {
        score += 10; // Adiciona 10 pontos ao atravessar uma rua
        last_road_index = current_road_index; // Atualiza a última rua atravessada
    }

    // Reseta a posição do jogador quando ele chega ao topo da tela
    if (player.y <= 1) {
        player.y = HEIGHT - 2; // Reinicia a posição do jogador
        // Move os carros para baixo
        for (int i = 0; i < TOTAL_ROADS; i++) {
            cars[i].y += ROAD_HEIGHT + 1;
            if (cars[i].y >= HEIGHT - 1) {
                cars[i].y = 1;
                cars[i].x = rand() % (WIDTH - 2 * SIDEWALK_WIDTH) + SIDEWALK_WIDTH;
            }
        }
        last_road_index = -1; // Reseta o índice ao reiniciar
    }
}


int play_game() {
    srand(time(NULL));
    load_high_scores(); // Carrega os recordes ao iniciar o jogo
    init_game();
    long last_frame_time = get_time();
    
    while (!game_over) {
        long current_time = get_time();
        
        if (keyhit()) {
            char input = readch();
            if (input == 27) { // 27 é o código ASCII para Esc
                game_over = 1; // Encerra o jogo
                break; // Sai do loop do jogo
            }
            handle_input(input);
        }

        if (current_time - last_frame_time >= 200) {
            update();
            last_frame_time = current_time;
        }
        
        delay(16);  // Delay de 16ms para limitar a 60 FPS
        render_game(); // Atualiza a renderização do jogo
    } 
    
    printf("Game Over! Sua pontuação: %d. Pressione Enter para voltar ao menu.\n", score);
    
    // Verifica se é um novo recorde
    if (score > high_scores[MAX_SCORES - 1].score) {
        char player_name[20];
        printf("Novo recorde! Sua pontuação: %d. Digite seu nome: ", score);
        scanf("%s", player_name); // Lê o nome do jogador
        update_high_scores(player_name, score); // Atualiza a tabela de recordes
        save_high_scores(); // Salva a nova tabela de recordes
    }

    show_high_scores(); // Mostra a tabela de recordes
    game_over = 0; // Reseta o estado do jogo
    return 0;
}
