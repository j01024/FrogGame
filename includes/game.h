#ifndef __GAME_H_GUARD__
#define __GAME_H_GUARD__
#include "frog.h"
#include "interfaces/events.h"
#include "interfaces/drawing.h"
#include "car.h"
#include "background.h"
#include "utility.h"

#define CARS_INITIAL_SIZE 10

typedef struct game{
    events* events;
    drawing* drawing;

    Frog* frog;
    Background* background;

    int __cars_num;
    int __cars_size;
    Car** cars; /*array of pointers (references)*/
}FrogGame;

extern FrogGame* Game; /*game is global variable, so we can access both frog and background data for rendering*/

void init_game(); /*initializes FrogGame* Game*/
FrogGame* new_game(); /*creates new instance of FrogGame*/
void delete_game(FrogGame* game); /*frees resources used by game*/
void game_update(void* this);
void game_draw_background(FrogGame* game, WINDOW* win); /*draws background on given window*/
void game_generate_background(FrogGame* game); /*generates new background for frog game*/
void game_draw(void* this, WINDOW* win, void* additional_data); /*draws all game object on given window, no additional data required, set additional_data to NULL*/

void add_car(FrogGame* game, Car* car); /*adds car to the game*/
void __cars_resize(FrogGame* game, int new_size); /*can be used also to change size to smaller*/
void __cars_clear(FrogGame* game); /*deletes all cars, sets size to initial size*/
/*if needed add __cars_remove, right now it doesnt seem to be needed*/


#endif