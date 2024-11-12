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
int score = 0; 
int last_road_index = -1; 

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
                high_scores[j] = high_scores[j - 1]; 
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
    while (get_keypress() != 10); 
}

void init_game() {
    player.x = WIDTH / 2;
    player.y = HEIGHT - 2;
    score = 0; 
    last_road_index = -1; 

    
    for (int i = 0; i < TOTAL_ROADS; i++) {
        cars[i].y = i * (ROAD_HEIGHT + 1) + 1;

        if (difficulty == 3) { 
            
            cars[i].x = rand() % (WIDTH - 2 * SIDEWALK_WIDTH - 6) + SIDEWALK_WIDTH; 
        } else {
            cars[i].x = rand() % (WIDTH - 2 * SIDEWALK_WIDTH) + SIDEWALK_WIDTH;
        }
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
        o
        if (cars[i].y == player.y) {
            
            if (player.x >= cars[i].x - 1 && player.x <= cars[i].x + 6) { 
                game_over = 1; 
                break; 
            }
        }
    }

    
    int current_road_index = player.y / (ROAD_HEIGHT + 1);
    
    
    if (current_road_index < TOTAL_ROADS && current_road_index != last_road_index) {
        score += 10; 
        last_road_index = current_road_index; 
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
        last_road_index = -1; 
    }
}


int play_game() {
    srand(time(NULL));
    load_high_scores(); 
    init_game();
    long last_frame_time = get_time();
    
    while (!game_over) {
        long current_time = get_time();
        
        if (keyhit()) {
            char input = readch();
            if (input == 27) { 
                game_over = 1; 
                break; 
            }
            handle_input(input);
        }

        if (current_time - last_frame_time >= 200) {
            update();
            last_frame_time = current_time;
        }
        
        delay(16);  
        render_game(); 
    } 
    
    printf("Game Over! Sua pontuação: %d. Pressione Enter para voltar ao menu.\n", score);
    
    
    if (score > high_scores[MAX_SCORES - 1].score) {
        char player_name[20];
        printf("Novo recorde! Sua pontuação: %d. Digite seu nome: ", score);
        scanf("%s", player_name); 
        update_high_scores(player_name, score); 
        save_high_scores(); 
    }

    show_high_scores(); 
    game_over = 0; 
    return 0;
}
