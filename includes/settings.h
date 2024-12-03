#ifndef __SETTINGS_H_GUARD__
#define __SETTING_H_GUARD__
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BOARD_X_DEFAULT 100
#define BOARD_Y_DEFAULT 40

#define BOARD_BORDER_X 1
#define BOARD_BORDER_Y 1

#define FPS_DEFAULT 60

typedef struct settings_t{
    int fps;
    int size_board_x, size_board_y;
    char frog_char;
    char car_char;
    char obstacle_char;

    int lane_cars_min;
    int lane_cars_max;
    int roadside_obstacles_min;
    int roadside_obstacles_max;

    int frog_lives;
    int frog_jump_delay_ms;
}Settings;

Settings* new_settings();/*creates new settings with default values*/
void delete_settings(Settings* s);

Settings* load_from_file(char* filename); /*loads new settings from file, returns NULL if filename is not valid*/
void __settings_skip_name(FILE* f); /*skips everything till equals sign*/

#endif