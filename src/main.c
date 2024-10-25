#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"
#include "menu.h"

int main() {
    int ch = 0;

    // Inicializações da CLI-lib
    screenInit(1);
    keyboardInit();
    timerInit(50);
    screenUpdate();

    // Exibe o menu inicial
    display_menu();
    
    // Loop até que a tecla Enter ou Esc seja pressionada
    while (1) {
        if (keyhit()) {
            ch = readch();    
            handle_menu_input(ch);
            display_menu();  
        }
        
        // Se Enter for pressionado, inicia o jogo
        if (ch == 10) {
            play_game();
            ch = 0;
            display_menu(); // Retorna ao menu após o jogo
        } 
        // Se Esc for pressionado, sai do jogo
        else if (ch == 27) { // 27 é o código ASCII para Esc
            break; // Encerra o loop e sai do programa
        }
        
        if (timerTimeOver() == 1) {
            screenUpdate();
        }
    }

    // Desaloca recursos utilizados pela CLI-lib
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    
    return 0;
}
