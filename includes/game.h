#ifndef __GAME_H_GUARD__
#define __GAME_H_GUARD__
#include "frog.h"
#include "car.h"
#include "obstacle.h"
#include "interfaces/events.h"
#include "interfaces/drawing.h"
#include "background.h"
#include "utility.h"

#define CARS_INITIAL_SIZE 20
#define LANE_CARS_MIN 2 /*there are 2 cars minimum on the lane*/
#define LANE_CARS_MAX 6 /*there are maximum 6 cars on the lane*/

#define OBSTACLES_INITIAL_SIZE 20
#define ROADSIDE_OBSTACLES_MIN 2
#define ROADSIDE_OBSTACLES_MAX 6

typedef struct game_t{
    events* events;
    drawing* drawing;

    Frog* frog;
    Background* background;

    /*implementing vectors in C to work like template vectors in C++ is tricky, and requires writing macros
      i would like not to write macros and all that stinky code just for 2 vector like arrays*/

    int __cars_num;
    int __cars_size;
    Car** cars; /*array of pointers (references)*/

    int __obstacles_num;
    int __obstacles_size;
    Obstacle** obstacles; /*array of pointers (references)*/

    
}FrogGame;

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

void add_obstacle(FrogGame* game, Obstacle* o);
void __obstacles_resize(FrogGame* game, int new_size);
void __obstacles_clear(FrogGame* game);
/*if needed add __obstacles_remove, right now it doesnt seem to be needed*/


#endif