#ifndef __SETUP_H_GUARD__
#define __SETUP_H_GUARD__

#include <ncurses.h>
#include <stdlib.h> /*for rand()*/
#include <time.h> /*setup rand*/
#include "colors.h"
#include "settings.h"

extern WINDOW* WIN_BOARD;
extern WINDOW* WIN_INFO;

extern short SZ_TERMINAL_X, SZ_TERMINAL_Y;
extern short BOARD_X, BOARD_Y;

extern Settings* GAME_SETTINGS;

void setup();
void init_windows();
void app_force_close();

#endif