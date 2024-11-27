#ifndef __COLORS_H_GUARD__
#define __COLORS_H_GUARD__
#include <ncurses.h>
#include <stdbool.h>

extern chtype COLOR_DEFAULT;
extern chtype COLOR_FROG;

extern chtype COLOR_CAR_ENEMY;
extern chtype COLOR_CAR_FRIENDLY;
extern chtype COLOR_CAR_TELEPORTER;

extern chtype COLOR_ROAD;
extern chtype COLOR_PAVEMENT;
extern chtype COLOR_GRASS;

extern bool __colors_initalized;

void init_colors();

#endif