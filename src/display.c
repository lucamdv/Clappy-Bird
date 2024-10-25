#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "game.h"
// Remova qualquer função draw que possa estar aqui

char get_char_non_blocking() {
    char c;
    system("stty raw"); // Configura o terminal para modo raw
    c = getchar();
    system("stty cooked"); // Restaura o terminal para modo cooked
    return c;
}

