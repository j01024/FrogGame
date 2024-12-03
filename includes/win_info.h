#ifndef __WIN_INFO_H_GUARD__
#define __WIN_INFO_H_GUARD__

#include "ncurses.h"
#include "setup.h"
#include "string.h"

#define WIN_INFO_HEIGHT 5
#define WIN_INFO_PADDING BOARD_X/10

void info_init(WINDOW* win_info); /*prints strings that do not change like "score", "level", "lives"*/
void info_update_score(WINDOW* win_info, int score);
void info_update_level(WINDOW* win_info, int level);
void info_update_lives(WINDOW* win_info, int lives);

#endif