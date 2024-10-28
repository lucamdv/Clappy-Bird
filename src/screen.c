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
 // Exibe a pontuação no canto superior da tela
    screenGotoxy(1, 1); // Ajuste a posição conforme necessário
    printf("Pontuação: %d", score);
    
    // Atualiza a tela
    screenUpdate();
    
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
