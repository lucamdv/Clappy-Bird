#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "game.h" // Inclua o cabeçalho do jogo para acesso à variável difficulty

int current_option = 0; // Posição atual no menu
int difficulty_option = 0; // Posição atual na seleção de dificuldade
char *menu_items[] = {
    "Enter - Iniciar Jogo",
    "Esc - Sair do Jogo"
};
char *difficulty_items[] = {
    "1 - Facil",
    "2 - Medio",
    "3 - Dificil" // Nova opção de dificuldade
};

int total_menu_items = 2;
int total_difficulty_items = 3; 

// Função que exibe o menu principal com o título "Crossy Road"
void display_menu() {
    screenClear();

    // Exibir o título "Crossy Road" centralizado
    char *title = "Crossy Road";
    int title_length = strlen(title);
    int title_startX = (TITLE_WIDTH - title_length) / 2; // Centralizar o título horizontalmente
    int title_startY = 8; // Posição vertical do título

    // Exibe o título com uma fonte maior
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(title_startX, title_startY);
    printf("%s\n", title); // Adiciona uma nova linha após o título

    // Exibir as opções do menu centralizadas abaixo do título
    int startY = title_startY + 2; // Posição vertical das opções do menu
    for (int i = 0; i < total_menu_items; i++) {
        int startX = (TITLE_WIDTH - strlen(menu_items[i])) / 2; // Centralizar cada item do menu horizontalmente
        screenGotoxy(startX, startY + i);
        if (i == current_option) {
            screenSetColor(RED, DARKGRAY); // Destacar a opção selecionada
        } else {
            screenSetColor(CYAN, DARKGRAY); // Cor padrão para outros itens
        }
        printf("%s", menu_items[i]);
    }

    // Atualizar a tela
    screenUpdate();
}

// Função que exibe o menu de seleção de dificuldade
void display_difficulty_menu() {
    screenClear();

    // Exibir o título "Selecione a Dificuldade"
    char *title = "Selecione a Dificuldade";
    int title_length = strlen(title);
    int title_startX = (TITLE_WIDTH - title_length) / 2; // Centralizar o título horizontalmente
    int title_startY = 8; // Posição vertical do título

    // Exibe o título com uma fonte maior
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(title_startX, title_startY);
    printf("%s\n", title); // Adiciona uma nova linha após o título

    // Exibir as opções de dificuldade centralizadas abaixo do título
    int startY = title_startY + 2; // Posição vertical das opções de dificuldade
    for (int i = 0; i < total_difficulty_items; i++) {
        int startX = (TITLE_WIDTH - strlen(difficulty_items[i])) / 2; // Centralizar cada item do menu horizontalmente
        screenGotoxy(startX, startY + i);
        if (i == difficulty_option) {
            screenSetColor(RED, DARKGRAY); // Destacar a opção selecionada
        } else {
            screenSetColor(CYAN, DARKGRAY); // Cor padrão para outros itens
        }
        printf("%s", difficulty_items[i]);
    }

    // Atualizar a tela
    screenUpdate();
}

// Função que navega entre os itens do menu
void handle_menu_input(char ch) {
    if (ch == 'w' && current_option > 0) { // Sobe no menu
        current_option--;
    } else if (ch == 's' && current_option < total_menu_items - 1) { // Desce no menu
        current_option++;
    } else if (ch == 10) { // Enter
        if (current_option == 0) {
            display_difficulty_menu(); // Avança para a tela de seleção de dificuldade
        } else if (current_option == 1) {
            exit(0); // Sair do jogo
        }
    }
}

// Função que navega entre as dificuldades
void handle_difficulty_input(char ch) {
    if (ch == 'w' && difficulty_option > 0) { // Sobe na seleção de dificuldade
        difficulty_option--;
    } else if (ch == 's' && difficulty_option < total_difficulty_items - 1) { // Desce na seleção de dificuldade
        difficulty_option++;
    } else if (ch == 10) { // Enter
        // Atribuir a dificuldade escolhida e começar o jogo
        if (difficulty_option == 0) {
            difficulty = 1; // Dificuldade fácil
        } else if (difficulty_option == 1) {
            difficulty = 2; // Dificuldade média
        } else if (difficulty_option == 2) {
            difficulty = 3; // Dificuldade difícil
        }
        init_game(); // Inicializa o jogo
        render_game(); // Começa o jogo
    }
}