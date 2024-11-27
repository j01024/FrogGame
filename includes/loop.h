#ifndef __LOOP_H_GUARD__
#define __LOOP_H_GUARD__
#include <ncurses.h>
#include <time.h>
#include "frog.h"
#include "setup.h"
#include "game.h"
#include "background.h"

/*init all objects here*/
void init_loop();

/*all per frame updates goes here, if you need more loops add more functions and call them inside loop()*/
void update_loop();

/*main loop maintains steady FPS and calls all specialized updates*/
void loop();



#endif