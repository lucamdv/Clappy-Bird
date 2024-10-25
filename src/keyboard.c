#include "keyboard.h"
#include "game.h"

// Função para capturar a tecla pressionada
char get_keypress() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Mapeia as teclas para ações no jogo
void handle_input(char key) {
    if (key == 'w' && player.y > 1) player.y--;  // Mover para cima
    if (key == 's' && player.y < HEIGHT - 2) player.y++;  // Mover para baixo
    if (key == 'a' && player.x > SIDEWALK_WIDTH) player.x--;  // Mover para esquerda
    if (key == 'd' && player.x < WIDTH - SIDEWALK_WIDTH - 1) player.x++;  // Mover para direita
}
