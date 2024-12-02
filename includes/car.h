#ifndef __CAR_H_GUARD__
#define __CAR_H_GUARD__
#include "./interfaces/position.h"
#include "./interfaces/drawing.h"
#include "./interfaces/events.h"
#include "./frog.h"
#include "background.h"
#include <ncurses.h>

#define CAR_DIRECTION_RIGHT 1
#define CAR_DIRECTION_LEFT -1

#define CAR_SPEED_MIN 2
#define CAR_SPPED_MAX 8

#define FRIENDLY_CAR_CHANCE 10 /*10% chance for friendly car*/
#define ENEMY_CAR_CHANCE 85 /*85% chance for enemy car*/
#define TELEPORTER_CAR_CHANCE 5 /*5% chance for teleporter car*/

typedef enum car_type_t{
    CAR_ENEMY, /*normal car, kills frog*/
    CAR_FRIENDLY, /*does not kill frog, waits for its move*/
    CAR_TELEPORTER /*teleports frog to random place*/
}CarType;

typedef struct Car{
    float speed_per_second; /*speed is unit/sec, unit is 1 character width*/
    float __float_pos_x, __float_pos_y; /*we need higher resolution position, cause our car is gonna update once per frame*/
    Frog* frog_ref; /*cars often need frog data, so we keep frog reference, so it can use it in its update functions and etc...*/

    bool (*frog_collision)(void* this);/*checks if this car collided with frog. returns true if collision occured, false otherwise*/
    bool (*frog_in_range)(void* this);/*checks whether frog is in car range, used for friendly cars*/
    CarType car_type;

    int direction; /*direction should be 1 or -1 (right/left)*/

    position* old_position;
    position* position;
    drawing* drawing;
    events* events;
}Car;

void car_draw(void *this, WINDOW *win, void* additional_data);
void car_update(void *this);
void delete_car(Car *car);

bool car_check_collision_with_frog(void* this); /*checks if given car collided with frog. returns true if collision occured, false otherwise*/
bool car_check_frog_in_range(void* this); /*checks whether frog is in friendly car range*/

Car* new_car(const short pos_x, const short pos_y, float speed_per_second, Frog* frog_ref);
Car* new_random_car(const short pos_x, const short pos_y, Frog* frog_ref);


#endif