#ifndef MENU_H
#define MENU_H

extern int current_option;
extern int difficulty_option;

void display_menu();
void display_difficulty_menu();
void handle_menu_input(char ch);
void handle_difficulty_input(char ch);

#endif
