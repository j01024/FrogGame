#include "../includes/obstacle.h"

Obstacle* new_obstacle(const short pos_x, const short pos_y, Frog* frog_ref){
    Obstacle* o = (Obstacle*)malloc(sizeof(Obstacle));

    o->position = new_position(pos_x, pos_y);
    o->drawing = new_drawing();

    o->type = OBSTACLE_GRASS; /*set default obstacle type to grass*/
    o->frog_ref = frog_ref;

    o->frog_collision = obstacle_check_collision_with_frog;
    o->drawing->draw = obstacle_draw;

    return o;
}

void obstacle_draw(void* this, WINDOW* win, void* additional_data){
    Obstacle* o = (Obstacle*)this;

   chtype color;
   switch(o->type){
        case OBSTACLE_GRASS:{
            color = COLOR_OBSTACLE_GRASS;
            break;
        }
        case OBSTACLE_PAVEMENT:{
            color = COLOR_OBSTACLE_PAVEMENT;
            break;
        }
   }

   wattron(win, color);
   mvwaddch(win, o->position->y + BOARD_BORDER_Y, o->position->x + BOARD_BORDER_X, GAME_SETTINGS->obstacle_char);
   wattroff(win, color);
}

bool obstacle_check_collision_with_frog(void* this){
    Obstacle* o = (Obstacle*)this;

    if((o->position->x == o->frog_ref->position->x) &&
        (o->position->y == o->frog_ref->position->y))
            return true;

    return false;
}

void delete_obstacle(Obstacle* o){
    free(o->drawing);
    free(o->position);

    free(o);
}