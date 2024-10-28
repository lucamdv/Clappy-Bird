#ifndef GAME_H
#define GAME_H

#define WIDTH 40
#define HEIGHT 20
#define SIDEWALK_WIDTH 2
#define ROAD_HEIGHT 1 // Altura da rua (número de linhas que a rua ocupa)
#define TOTAL_ROADS ((HEIGHT - 2) / (ROAD_HEIGHT + 1)) // Total de ruas
#define NUM_CARS 10    // Número de carros
#define MAX_SCORES 5

typedef struct {
    char name[20];
    int score;
} HighScoreEntry;

extern HighScoreEntry high_scores[MAX_SCORES];

void save_high_scores();
void load_high_scores();
void update_high_scores(const char *player_name, int new_score);

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
extern int game_over;
extern int score; // Nova variável de pontuação

void init_game();
void update();
int play_game();
long get_time(); // Adicione a declaração

#endif // GAME_H
