#include "../includes/setup.h"

WINDOW* WIN_BOARD;
WINDOW* WIN_INFO;

short SZ_TERMINAL_X, SZ_TERMINAL_Y;
short BOARD_X = BOARD_X_DEFAULT, BOARD_Y = BOARD_Y_DEFAULT;

void setup(){
    initscr();
    clear(); 
    refresh();
    noecho(); /*disable character echo when inputting something*/
    cbreak();
    curs_set(0); /*disable cursor*/
    keypad(stdscr, TRUE); /*processing of special keys ARROW_UP, etc*/
    nodelay(stdscr, TRUE); /*getch() won't wait until key is pressed, will return ERR if no key is pressed*/

    if(has_colors())
        start_color();

    srand(time(NULL)); /*init random number generator*/
}

void init_windows(){
    getmaxyx(stdscr, SZ_TERMINAL_Y, SZ_TERMINAL_X);
    WIN_BOARD = newwin(BOARD_Y,BOARD_X,(SZ_TERMINAL_Y/2)-BOARD_Y/2, (SZ_TERMINAL_X/2)-BOARD_X/2);
    WIN_INFO = newwin(5,BOARD_X, (SZ_TERMINAL_Y/2)+BOARD_Y/2, (SZ_TERMINAL_X/2)-BOARD_X/2);

    /*windws background colors*/
    wbkgd(WIN_BOARD, COLOR_FROG);
    wbkgd(WIN_INFO, COLOR_DEFAULT);

    box(WIN_BOARD,0,0); //looks cool with border
    box(WIN_INFO,0,0);
}