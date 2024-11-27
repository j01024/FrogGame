#ifndef __SETUP_H_GUARD__
#define __SETUP_H_GUARD__

#include <ncurses.h>
#include <stdlib.h> /*for rand()*/
#include <time.h> /*setup rand*/
#include "colors.h"
#define BOARD_X_DEFAULT 100
#define BOARD_Y_DEFAULT 40

#define BOARD_BORDER_X 1
#define BOARD_BORDER_Y 1
#define FPS 60

extern WINDOW* WIN_BOARD;
extern WINDOW* WIN_INFO;

extern short SZ_TERMINAL_X, SZ_TERMINAL_Y;
extern short BOARD_X, BOARD_Y;

void setup();
void init_windows();

#endif