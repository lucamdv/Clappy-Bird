#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"
#include "menu.h"

int main() {
    int ch = 0;

    
    screenInit(1);
    keyboardInit();
    timerInit(50);
    screenUpdate();

    
    load_high_scores(); 

    
    display_menu();
    
    
    while (1) {
        if (keyhit()) {
            ch = readch();    
            handle_menu_input(ch); 
            display_menu();  
        }
        
        
        if (ch == 10 && current_option == 0) { 
            display_difficulty_menu(); 

            
            while (1) {
                if (keyhit()) {
                    ch = readch();    
                    handle_difficulty_input(ch); 
                    display_difficulty_menu(); 

                    
                    if (ch == 10) {
                        play_game(); 
                        ch = 0; 
                        show_high_scores;
                        break; 
                    }
                }

                if (timerTimeOver() == 1) {
                    screenUpdate();
                }
            }
        } 
        
        else if (ch == 27) { 
            break; 
        }
        
        if (timerTimeOver() == 1) {
            screenUpdate();
        }
    }

    
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    
    return 0;
}
