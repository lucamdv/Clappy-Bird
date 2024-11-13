#ifndef GAME_H
#define GAME_H

#define WIDTH 40
#define HEIGHT 20
#define SIDEWALK_WIDTH 2
#define ROAD_HEIGHT 1 
#define TOTAL_ROADS ((HEIGHT - 2) / (ROAD_HEIGHT + 1))
#define MAX_SCORES 5
#define EASY 1
#define MEDIUM 2



typedef struct {
    char name[20];
    int score;
} HighScoreEntry;


typedef struct {
    int x;
    int y;
} Player;

typedef struct {
    int x;
    int y;
    int direction;
} Car;

extern HighScoreEntry high_scores[MAX_SCORES];
extern Player player;
extern Car cars[];
extern int game_over;
extern int score; 
extern int difficulty; 

void init_game();
void update();
int play_game();
long get_time(); 
void show_high_scores();
void save_high_scores();
void load_high_scores();
void update_high_scores(const char *player_name, int new_score);

#endif // GAME_H
