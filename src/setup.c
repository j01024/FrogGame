#include "../includes/setup.h"

WINDOW* WIN_BOARD;
WINDOW* WIN_INFO;

short SZ_TERMINAL_X, SZ_TERMINAL_Y;
short BOARD_X, BOARD_Y; /*leave those for backward compatibility*/
Settings* GAME_SETTINGS;

void setup(Settings* s){
    if(s!=NULL) GAME_SETTINGS=s;
    else GAME_SETTINGS = new_settings();

    BOARD_X = GAME_SETTINGS->size_board_x;
    BOARD_Y = GAME_SETTINGS->size_board_y;

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

    if(SZ_TERMINAL_X < BOARD_X || SZ_TERMINAL_Y < BOARD_Y){
        wprintw(stdscr, "Your screen is too small to display this game\nRequired window size: X=%d Y=%d", BOARD_X, BOARD_Y);
        wrefresh(stdscr); /*otherwise message won't display*/
        getchar();
        endwin();
        exit(1);
    }


    WIN_BOARD = newwin(BOARD_Y,BOARD_X,(SZ_TERMINAL_Y/2)-BOARD_Y/2, (SZ_TERMINAL_X/2)-BOARD_X/2);
    WIN_INFO = newwin(5,BOARD_X, (SZ_TERMINAL_Y/2)+BOARD_Y/2, (SZ_TERMINAL_X/2)-BOARD_X/2);

    /*windws background colors*/
    wbkgd(WIN_BOARD, COLOR_FROG);
    wbkgd(WIN_INFO, COLOR_DEFAULT);

    box(WIN_BOARD,0,0); //looks cool with border
    box(WIN_INFO,0,0);
}

/*forces pretty safe closing of app*/
void app_force_close(){
    endwin();
    exit(0);
    /*add more necessary things if needed*/
}