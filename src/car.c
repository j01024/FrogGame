#include "../includes/car.h"

Car *new_car(const short pos_x, const short pos_y, float speed_per_second)
{
    Car *c = (Car *)malloc(sizeof(Car));
    c->car_type = CAR_ENEMY; /*set default car type*/

    c->drawing = new_drawing();
    c->events = new_events();
    c->position = new_position(pos_x, pos_y);
    c->old_position = new_position(pos_x, pos_y);

    c->drawing->draw = car_draw;
    c->events->update = car_update;

    c->__float_pos_x = (float)pos_x;
    c->__float_pos_y = (float)pos_y;
    c->speed_per_second = speed_per_second;

    c->frog_collision = check_collision_with_frog;

    return c;
}

/*draws car on given window*/
void car_draw(void *this, WINDOW *win, void *additional_data)
{
    Background *bg = (Background *)additional_data;
    assert(bg != NULL && "Background data has not been passed. Please pass Background data for Frog drawing function");
    Car *c = (Car *)this;
    chtype old_color = bg->tiles[c->old_position->y][c->old_position->x]->color; /*color on old position*/

    wattron(win, old_color);
    mvwaddch(win, c->old_position->y + BOARD_BORDER_Y, c->old_position->x + BOARD_BORDER_X, ' '); /*clear previous position*/
    wrefresh(win);                                                                                /*refresh window, otherwise we will have rendering artifacts and I don't know why*/

    /*get proper car color depending on its type*/
    chtype car_color;
    switch (c->car_type){
        case CAR_ENEMY:{
            car_color = COLOR_CAR_ENEMY;
            break;
        }
        case CAR_FRIENDLY:{
            car_color = COLOR_CAR_FRIENDLY;
            break;
        }
        case CAR_TELEPORTER:{
            car_color = COLOR_CAR_TELEPORTER;
            break;
        }
    }

    wattron(win, car_color);
    mvwaddch(win, c->position->y + BOARD_BORDER_Y, c->position->x + BOARD_BORDER_X, '*'); /*+1 to omit border*/
    wattroff(win, car_color);
}

void car_update(void *this)
{
    Car *c = (Car *)this;

    c->old_position->x = c->position->x;
    c->old_position->y = c->position->y;

    if (!is_proper_coordinate(c->position->x + 1, c->position->y))
    {
        c->position->x = 0;
        c->__float_pos_x = 0.0; /*don't forget also about it*/
        return;                 /*TODO: despawn car, or change its direction*/
    }

    c->__float_pos_x += c->speed_per_second / FPS;
    c->position->x = c->__float_pos_x; /*this automatically casts float to short, working like floor functions. This will ceil for negative numbers though*/
}

bool check_collision_with_frog(void *this, void *frog)
{
    Frog *f = (Frog *)frog;
    Car *c = (Car *)this;

    if (c->position->x == f->position->x && c->position->y == f->position->y)
        return true;

    return false;
}

void delete_car(Car *car)
{
    free(car->position);
    free(car->old_position);
    free(car->drawing);
    free(car->old_position);

    free(car);
}