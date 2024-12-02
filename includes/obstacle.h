#ifndef __OBSTACLE_H_GUARD__
#define __OBSTACLE_H_GUARD__
#include "./interfaces/position.h"
#include "./interfaces/drawing.h"
#include "frog.h"
#include <ncurses.h>

typedef enum obstacle_type_t{
    OBSTACLE_GRASS,
    OBSTACLE_PAVEMENT
}ObstacleType;


typedef struct obstacle_t{
    position* position;
    drawing* drawing;
    ObstacleType type;

    Frog* frog_ref; /*frog ref is used to determine collisions with frogs and obstacles*/
    bool(*frog_collision)(void* this);
}Obstacle;

Obstacle* new_obstacle(const short pos_x, const short pos_y, Frog* frog_ref);
void delete_obstacle(Obstacle* o);

void obstacle_draw(void* this, WINDOW* win, void* additional_data); /*additional data can be set to null*/
bool obstacle_check_collision_with_frog(void* this);

#endif