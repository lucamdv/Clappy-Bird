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

    // Carrega recordes antes de exibir o menu
    load_high_scores(); 

    // Exibe o menu inicial
    display_menu();
    
    // Loop até que a tecla Enter ou Esc seja pressionada
    while (1) {
        if (keyhit()) {
            ch = readch();    
            handle_menu_input(ch); // Processa a entrada do menu
            display_menu();  
        }
        
        // Se Enter for pressionado e o usuário estiver no menu principal
        if (ch == 10 && current_option == 0) { // Verifica se está na opção de iniciar jogo
            display_difficulty_menu(); // Exibe o menu de seleção de dificuldade

            // Enquanto a dificuldade não for escolhida, espera pela entrada do usuário
            while (1) {
                if (keyhit()) {
                    ch = readch();    
                    handle_difficulty_input(ch); // Processa a entrada da dificuldade
                    display_difficulty_menu(); // Atualiza a tela de dificuldade

                    // Se Enter for pressionado, inicia o jogo
                    if (ch == 10) {
                        play_game(); // Inicia o jogo
                        ch = 0; // Reseta a entrada
                        show_high_scores;
                        break; // Sai do loop de dificuldade
                    }
                }

                if (timerTimeOver() == 1) {
                    screenUpdate();
                }
            }
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
