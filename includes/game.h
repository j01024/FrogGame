#ifndef __GAME_H_GUARD__
#define __GAME_H_GUARD__
#include "frog.h"
#include "car.h"
#include "obstacle.h"
#include "interfaces/events.h"
#include "interfaces/drawing.h"
#include "background.h"
#include "utility.h"
#include "win_info.h"

#define CARS_INITIAL_SIZE 20
#define OBSTACLES_INITIAL_SIZE 20

typedef struct game_t{
    int score, level;

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

void game_init_info(FrogGame* game, WINDOW* win_info);

FrogGame* new_game(); /*creates new instance of FrogGame*/
void delete_game(FrogGame* game); /*frees resources used by game*/

void game_update(void* this);
void game_update_cars(FrogGame* game);
void game_update_obstacles(FrogGame* game);

void game_level_end(FrogGame* game);
void game_lose(FrogGame* game);

void game_draw_background(FrogGame* game, WINDOW* win); /*draws background on given window*/
void game_generate_background(FrogGame* game); /*generates new background for frog game*/
void game_draw(void* this, WINDOW* win, void* additional_data); /*draws all game object on given window, no additional data required, set additional_data to NULL*/

void add_car(FrogGame* game, Car* car); /*adds car to the game*/
void __cars_resize(FrogGame* game, int new_size); /*can be used also to change size to smaller*/
void __cars_clear(FrogGame* game); /*deletes all cars, sets size to initial size*/
/*if needed add __cars_remove, right now it doesnt seem to be needed*/

void add_obstacle(FrogGame* game, Obstacle* o);/*adds obstacle to the game*/
void __obstacles_resize(FrogGame* game, int new_size); /*can be used also to change size to smaller*/
void __obstacles_clear(FrogGame* game); /*deletes all obstacles, sets size to initial size*/
/*if needed add __obstacles_remove, right now it doesnt seem to be needed*/

extern const char* game_over_big[];/*53x25*/
extern const char* game_over_small[];/*31x9*/

#endif