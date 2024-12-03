#ifndef __FROG_H_GUARD__
#define __FROG_H_GUARD__
#include "./interfaces/position.h"
#include "./interfaces/drawing.h"
#include "./interfaces/events.h"
#include "colors.h"
#include "ctype.h"
#include "utility.h"
#include "background.h"
#include <ncurses.h>

#define FROG_MOVE_DELAY 0.1f

typedef struct frog_t
{
    int lives;

    position* old_position; /*old position is used to erase previous position to prevent clearing whole screen while drawing*/
    position *position;
    drawing *drawing;
    events *events;

    clock_t last_jump_time;

    void (*enemy_car_collision)(void* this); /*event trigerred when car hits frog, car should have its own collision event to prevent circular dependencies*/
    void (*friendly_car_collision)(void* this);
    void (*teleporter_car_collision)(void* this);
    void(*obstacle_collision)(void* this);
    void(*level_end)(void* this);

}Frog;

void frog_draw(void *this, WINDOW *win, void* additional_data); /*set additional_data expects pointer to background to be present*/
void frog_update(void *this);

void frog_enemy_car_collision(void* this);
void frog_friendly_car_collision(void* this);
void frog_teleporter_car_collision(void* this);

void frog_obstacle_collision(void* this);

void frog_level_end(void* this);

Frog *new_frog(const short pos_x, const short pos_y);
void delete_frog(Frog *frog);

#endif