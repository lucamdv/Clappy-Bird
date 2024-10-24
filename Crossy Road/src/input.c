#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "input.h"

// Função para configurar a entrada de teclado
char get_char_non_blocking() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return '\0';
}
