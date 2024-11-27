#include "../includes/frog.h"


void frog_draw(void *this, WINDOW *win, void* additional_data)
{ 
    Background* bg = (Background*)additional_data;
    assert(bg!=NULL && "Background data has not been passed. Please pass Background data for Frog drawing function");
    /*draws frog on given window*/
    Frog *f = (Frog *)this;
    chtype old_color = bg->tiles[f->old_position->y][f->old_position->x]->color; /*color on old position*/

    wattron(win, old_color);
    mvwaddch(win, f->old_position->y+1, f->old_position->x+1,' '); /*clear previous position*/
    wrefresh(win); /*refresh window, otherwise we will have rendering artifacts and I don't know why*/

    wattron(win, COLOR_FROG);
    mvwaddch(win, f->position->y + BOARD_BORDER_Y, f->position->x + BOARD_BORDER_X, '#'); /*+1 to omit border*/
    wattroff(win, COLOR_FROG);
}

void frog_update(void *this)
{
    Frog *f = (Frog *)this;
    int keycode = getch();
    keycode=tolower(keycode);

    f->old_position->x = f->position->x;
    f->old_position->y = f->position->y;


    /*TODO: when i will add collision to the frog, put this code in separate function to keep update function clear and readable*/
    switch (keycode)
    {
    case 'w':{
        if(!is_proper_coordinate(f->position->x, f->position->y - 1))
            break;
        f->position->y--; /*note that OY axis in terminal coordinate system works vice versa*/
        break;
    }
    case 'a':{
        if(!is_proper_coordinate(f->position->x-1, f->position->y))
            break;
        f->position->x--;
        break;
    }
    case 's':{
        if(!is_proper_coordinate(f->position->x, f->position->y+1)) /*-1 since indexing starts from 0, don't forget about borders*/
            break;
        f->position->y++;
        break;
    }
    case 'd':{
        if(!is_proper_coordinate(f->position->x+1, f->position->y)) /*-1 since indexing starts from 0, don't forget about borders*/
            break;
        f->position->x++;
        break;
    }
    default:
        break;
    }
}

Frog *new_frog(const short pos_x, const short pos_y)
{
    Frog *f = (Frog *)malloc(sizeof(Frog));

    /*setup frog struct*/

    /*position*/
    f->position = new_position(pos_x, pos_y);
    f->old_position = new_position(pos_x,pos_y);

    /*drawing functions */
    f->drawing = new_drawing();
    f->drawing->draw = frog_draw;

    /*update*/
    f->events = new_events();
    f->events->update = frog_update;

    /*collision with different objects*/
    f->enemy_car_collision = frog_enemy_car_collision;
    f->friendly_car_collision = frog_friendly_car_collision;
    f->teleporter_car_collision = frog_teleporter_car_collision;

    return f;
}

void frog_enemy_car_collision(void* this){
    Frog* f = (Frog*)this;
    f->position->x=0;
    f->position->y=0;
}

void frog_friendly_car_collision(void* this){ /*well if you somehow collide with friendly car, you should bounce to your previous position*/
    Frog* f = (Frog*)this;

    f->position->x = f->old_position->x;
    f->position->y = f->old_position->y;
}

void frog_teleporter_car_collision(void* this){
        Frog* f = (Frog*)this;

    /*bounce*/
    f->position->x= rand_in_range(0, BOARD_X - (2*BOARD_BORDER_X) -1);
    f->position->y= rand_in_range(0, BOARD_Y - (2*BOARD_BORDER_Y) -1);
}


void delete_frog(Frog *frog)
{
    free(frog->drawing);
    free(frog->position);
    free(frog->events);
    free(frog);
}