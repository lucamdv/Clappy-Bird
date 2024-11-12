#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdio.h>
#include <unistd.h>
#include <termios.h>


char get_keypress();


void handle_input(char key);

void keyboardInit();

void keyboardDestroy();
    
int keyhit();

int readch();

#endif // KEYBOARD_H
