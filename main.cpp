#include <ncurses.h>
#include "game.h"

int main() {

    //Initialize ncurses
    initscr();
    
    //Don't buffer input 
    cbreak(); 

    //Enable input from special keys
    keypad(stdscr, TRUE);

    //Don't echo input
    noecho(); 

    //Don't display cursor
    curs_set(0); 

    //Update screen initially (prevents getch() from clearing the screen)
    refresh(); 

    //Set getch() to non-blocking mode
    nodelay(stdscr, TRUE); 

    game();

    return 0;
}