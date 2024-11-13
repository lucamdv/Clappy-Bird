#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "game.h" 

int current_option = 0; 
int difficulty_option = 0; 
char *menu_items[] = {
    "Enter - Iniciar Jogo",
    "Esc - Sair do Jogo"
};
char *difficulty_items[] = {
    "1 - Facil",
    "2 - Medio",
    "3 - Dificil" 
};

int total_menu_items = 2;
int total_difficulty_items = 3; 

void display_menu() {
    screenClear();

    char *title = "Crossy Road";
    int title_length = strlen(title);
    int title_startX = (TITLE_WIDTH - title_length) / 2; 
    int title_startY = 8; 

    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(title_startX, title_startY);
    printf("%s\n", title); 

    int startY = title_startY + 2; 

    for (int i = 0; i < total_menu_items; i++) {
        int startX = (TITLE_WIDTH - strlen(menu_items[i])) / 2; 
        screenGotoxy(startX, startY + i);
        if (i == current_option) {
            screenSetColor(RED, DARKGRAY); 
        } else {
            screenSetColor(CYAN, DARKGRAY); 
        }
        printf("%s", menu_items[i]);
    }

    screenUpdate();
}

void display_difficulty_menu() {
    screenClear();

    char *title = "Selecione a Dificuldade";
    int title_length = strlen(title);
    int title_startX = (TITLE_WIDTH - title_length) / 2;
    int title_startY = 8; 

    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(title_startX, title_startY);
    printf("%s\n", title); 

    int startY = title_startY + 2; 
    for (int i = 0; i < total_difficulty_items; i++) {
        int startX = (TITLE_WIDTH - strlen(difficulty_items[i])) / 2; 
        screenGotoxy(startX, startY + i);
        if (i == difficulty_option) {
            screenSetColor(RED, DARKGRAY); 
        } else {
            screenSetColor(CYAN, DARKGRAY); 
        }
        printf("%s", difficulty_items[i]);
    }

    screenUpdate();
}

void handle_menu_input(char ch) {
    if (ch == 'w' && current_option > 0) { 
        current_option--;
    } else if (ch == 's' && current_option < total_menu_items - 1) { 
        current_option++;
    } else if (ch == 10) { 
        if (current_option == 0) {
            display_difficulty_menu(); 
        } else if (current_option == 1) {
            exit(0); 
        }
    }
}

void handle_difficulty_input(char ch) {
    if (ch == 'w' && difficulty_option > 0) { 
        difficulty_option--;
    } else if (ch == 's' && difficulty_option < total_difficulty_items - 1) { 
        difficulty_option++;
    } else if (ch == 10) { 
        if (difficulty_option == 0) {
            difficulty = 1; 
        } else if (difficulty_option == 1) {
            difficulty = 2; 
        } else if (difficulty_option == 2) {
            difficulty = 3; 
        }
        init_game();
        render_game(); 
    }
}