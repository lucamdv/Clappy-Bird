#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "game.h"

int difficulty;  

void clear_screen() {
    system("clear");
}


void render_game() {
    clear_screen();  

    
    screenGotoxy(1, 1); 
    printf("Pontuação: %d", score);
    
    
    for (int x = 0; x < WIDTH + 2; x++) printf("-");
    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("|");  

        for (int x = 0; x < WIDTH; x++) {
            if (y == player.y && x == player.x) {
                printf("🐔");  
            } else {
                int is_car = 0;

                
                for (int i = 0; i < TOTAL_ROADS; i++) {
                    if (y == cars[i].y) { /
                        if (difficulty == 3) { 
                            if (x == cars[i].x || x == cars[i].x + 4 || x == cars[i].x + 8) {
                                printf("🚗");
                                is_car = 1;
                                break;
                            }
                        } else if (difficulty == 2) { 
                            if (x == cars[i].x || x == cars[i].x + 6) {
                                printf("🚗");
                                is_car = 1;
                                break;
                            }
                        } else { 
                            if (x == cars[i].x) {
                                printf("🚗");
                                is_car = 1;
                                break;
                            }
                        }
                    }
                }

                if (!is_car) {
                    if (y % (ROAD_HEIGHT + 1) == 0) {
                        printf("██");  
                    } else {
                        printf("  ");  
                    }
                }
            }
        }
        printf("|\n");
    }

    for (int x = 0; x < WIDTH + 2; x++) printf("-");
    printf("\n");

    
    screenUpdate();
}



void screenDrawBorders() {
    char hbc = BOX_HLINE;
    char vbc = BOX_VLINE;

    screenClear();
    screenBoxEnable();

    screenGotoxy(MINX, MINY);
    printf("%c", BOX_UPLEFT);

    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }
    screenGotoxy(MAXX, MINY);
    printf("%c", BOX_UPRIGHT);

    for (int i = MINY + 1; i < MAXY; i++) {
        screenGotoxy(MINX, i);
        printf("%c", vbc);
        screenGotoxy(MAXX, i);
        printf("%c", vbc);
    }

    screenGotoxy(MINX, MAXY);
    printf("%c", BOX_DWNLEFT);
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MAXY);
        printf("%c", hbc);
    }
    screenGotoxy(MAXX, MAXY);
    printf("%c", BOX_DWNRIGHT);

    screenBoxDisable();
}

void screenInit(int drawBorders) {
    screenClear();
    if (drawBorders) screenDrawBorders();
    screenHomeCursor();
    screenHideCursor();
}

void screenDestroy() {
    printf("%s[0;39;49m", ESC); // Reset colors
    screenSetNormal();
    screenClear();
    screenHomeCursor();
    screenShowCursor();
}

void screenGotoxy(int x, int y) {
    x = (x < 0 ? 0 : x >= MAXX ? MAXX - 1 : x);
    y = (y < 0 ? 0 : y > MAXY ? MAXY : y);

    printf("%s[f%s[%dB%s[%dC", ESC, ESC, y, ESC, x);
}

void screenSetColor(screenColor fg, screenColor bg) {
    char atr[] = "[0;";

    if (fg > LIGHTGRAY) {
        atr[1] = '1';
        fg -= 8;
    }

    printf("%s%s%d;%dm", ESC, atr, fg + 30, bg + 40);
}
