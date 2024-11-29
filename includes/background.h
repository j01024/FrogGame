#ifndef __BACKGROUND_H_GUARD__
#define __BACKGROUND_H_GUARD__
#include <ncurses.h>
#include <stdbool.h>
#include "colors.h"
#include "setup.h"
#include "utility.h"
#include <stdlib.h>
#include <assert.h>


typedef struct background_tile_t{
    char key;
    chtype color;
}BackgroundTile;

extern BackgroundTile* tile_default; /*default tile which will be used by initializer functions*/
extern BackgroundTile* tile_road;
extern BackgroundTile* tile_grass;
extern BackgroundTile* tile_pavement;
extern bool __background_initialized; /*when init is called this is set to true, so functions which uses background can be sure that it is initalized*/


typedef struct background_t{
    int width, height;
    BackgroundTile*** tiles; /*dobule array of pointers (references)*/
}Background;

void init_background() /*inits basic background tiles for use*/;
Background* new_background(int width, int height); /*creates new background with given width an height*/
void fill_background(Background* bg, BackgroundTile* tile); /*fills background with given tile*/
void delete_background(Background* bg); /*frees memory used by background*/

void background_fill_area(Background* bg, int x, int y, int width, int height, BackgroundTile* tile); /*fills rectangular area in size width x height  starting from x,y coordinate filling it with given tile*/
BackgroundTile* get_random_tile(); /*helper function so we don't have to think aboout all tiles*/

#endif