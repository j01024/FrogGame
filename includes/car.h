#ifndef __CAR_H_GUARD__
#define __CAR_H_GUARD__
#include "./interfaces/position.h"
#include "./interfaces/drawing.h"
#include "./interfaces/events.h"
#include "./frog.h"
#include "background.h"
#include <ncurses.h>

typedef enum car_type_t{
    CAR_ENEMY, /*normal car, kills frog*/
    CAR_FRIENDLY, /*does not kill frog, waits for its move*/
    CAR_TELEPORTER /*teleports frog to random place*/
}CarType;

typedef struct Car{
    float speed_per_second; /*speed is unit/sec, unit is 1 character width*/
    float __float_pos_x, __float_pos_y; /*we need higher resolution position, cause our car is gonna update once per frame*/

    bool (*frog_collision)(void* this, void* frog);/*checks if this car collided with frog. returns true if collision occured, false otherwise*/
    CarType car_type;

    position* old_position;
    position* position;
    drawing* drawing;
    events* events;
}Car;

void car_draw(void *this, WINDOW *win, void* additional_data);
void car_update(void *this);
void delete_car(Car *car);

bool check_collision_with_frog(void* this, void* frog); /*checks if given car collided with frog. returns true if collision occured, false otherwise*/

Car* new_car(const short pos_x, const short pos_y, float speed_per_second);

#endif