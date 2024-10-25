#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

// Captura a tecla pressionada sem bloquear o terminal
char get_keypress();

// Mapeia a tecla pressionada para uma ação no jogo
void handle_input(char key);

void keyboardInit();

void keyboardDestroy();
    
int keyhit();

int readch();

#endif // KEYBOARD_H
