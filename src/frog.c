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
    mvwaddch(win, f->position->y + BOARD_BORDER_Y, f->position->x + BOARD_BORDER_X, GAME_SETTINGS->frog_char); /*+1 to omit border*/
    wattroff(win, COLOR_FROG);
}

void frog_update(void *this)
{
    clock_t time = clock();
    Frog *f = (Frog *)this;

    /*if there was not enough delay before last jump, we cannot move, so input should be ignored for frog*/
    if((time-f->last_jump_time)/(double)CLOCKS_PER_SEC < GAME_SETTINGS->frog_jump_delay_ms/1000.0) /*divide by 1000 to get seconds*/
        return;

    f->last_jump_time = time;

    int keycode = getch();
    flushinp(); /*flush input, otherwise characters gets buffered and its frustrating*/
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
    f->obstacle_collision = frog_obstacle_collision;
    f->level_end = frog_level_end;

    f->lives=GAME_SETTINGS->frog_lives;

    return f;
}

void frog_enemy_car_collision(void* this){
    Frog* f = (Frog*)this;
    f->lives--;

    /*set frog at the beginning of the level*/
    f->position->x=BOARD_X/2;
    f->position->y=BOARD_Y-2*BOARD_BORDER_Y-1;
}

void frog_friendly_car_collision(void* this){
    Frog* f = (Frog*)this;

    /*well if you somehow collide with friendly car, you should bounce to your previous position*/
    f->position->x = f->old_position->x;
    f->position->y = f->old_position->y;
}

void frog_teleporter_car_collision(void* this){
    Frog* f = (Frog*)this;

    f->position->x= rand_in_range(0, BOARD_X - (2*BOARD_BORDER_X) -1);
    f->position->y= rand_in_range(0, BOARD_Y - (2*BOARD_BORDER_Y) -1);
}

void frog_obstacle_collision(void* this){
    Frog* f = (Frog*)this;

    /*frog bounces to the previous position*/
    f->position->x = f->old_position->x;
    f->position->y = f->old_position->y;
}

void frog_level_end(void* this){
    Frog* f = (Frog*)this;

    /*reset lives*/
    f->lives = GAME_SETTINGS->frog_lives;

    /*set frog at the beginning of the level*/
    f->position->x=BOARD_X/2;
    f->position->y=BOARD_Y-2*BOARD_BORDER_Y-1;
}


void delete_frog(Frog *frog)
{
    free(frog->drawing);
    free(frog->position);
    free(frog->events);
    free(frog);
}