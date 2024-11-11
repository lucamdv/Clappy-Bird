#include "cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void cli_clear() {
    system("clear");
}

char cli_getch() {
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

void cli_putch(char ch) {
    putchar(ch);
    fflush(stdout);
}
