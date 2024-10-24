#ifndef GAME_H
#define GAME_H

#define WIDTH 40
#define HEIGHT 20
#define SIDEWALK_WIDTH 2
#define ROAD_HEIGHT 1 // Altura da rua (número de linhas que a rua ocupa)
#define TOTAL_ROADS ((HEIGHT - 2) / (ROAD_HEIGHT + 1)) // Total de ruas
#define NUM_CARS 10    // Número de carros

typedef struct {
    int x;
    int y;
} Player;

typedef struct {
    int x;
    int y;
    int direction;
} Car;

extern Player player;
extern Car cars[];

void init_game();
void update();
int play_game();

#endif // GAME_H
