#include "../includes/settings.h"

Settings* load_from_file(char* filename){
    FILE* f = fopen(filename, "r");
    if(f==NULL) return NULL;

    /*load settings, settings has to be in strict order, otherwise they will not work*/
    /*settings can also have names, after which should be '=' sign*/

    Settings* s =(Settings*)malloc(sizeof(Settings));

    /*fps*/
    __settings_skip_name(f);
    fscanf(f, "%d", &s->fps);

    /*board x*/
    __settings_skip_name(f);
    fscanf(f, "%d", &s->size_board_x);

    /*board y*/
     __settings_skip_name(f);
    fscanf(f, "%d", &s->size_board_y);

    /*frog_char*/
    __settings_skip_name(f);
    fscanf(f, "%c", &s->frog_char);

    /*car_char*/
    __settings_skip_name(f);
    fscanf(f, "%c", &s->car_char);

    /*obstacle_char*/
    __settings_skip_name(f);
    fscanf(f, "%c", &s->obstacle_char);

    /*lane_cars_min*/
    __settings_skip_name(f);
    fscanf(f, "%d", &s->lane_cars_min);

    /*lane_cars_max*/
    __settings_skip_name(f);
    fscanf(f, "%d", &s->lane_cars_max);

    /*roadside_obstacles_min*/
    __settings_skip_name(f);
    fscanf(f, "%d", &s->roadside_obstacles_min);

    /*roadside_obstacles_max*/
    __settings_skip_name(f);
    fscanf(f, "%d", &s->roadside_obstacles_max);

    /*frog_lives*/
    __settings_skip_name(f);
    fscanf(f, "%d", &s->frog_lives);

    /*frog_jump_delay*/
    __settings_skip_name(f);
    fscanf(f, "%d", &s->frog_jump_delay_ms);

    return s;
}

/*skips everything till equal sign*/
void __settings_skip_name(FILE* f){
    char c;
    while(fgetc(f)!='='){}
    while(isspace(c = fgetc(f))){} /*skip whitespaces after '=' sign*/
    ungetc(c,f); /*previous loop terminated when character was not space character, so we have to putback last character, otherwise we will lose it*/
}

Settings* new_settings(){
    Settings* s = (Settings*)malloc(sizeof(Settings));

    s->fps=FPS_DEFAULT;
    s->size_board_x=BOARD_X_DEFAULT;
    s->size_board_y=BOARD_Y_DEFAULT;
    s->frog_char='#';
    s->car_char='*';
    s->obstacle_char='$';

    s->lane_cars_min=2;
    s->lane_cars_max=6;
    s->roadside_obstacles_min=2;
    s->roadside_obstacles_max=6;

    s->frog_lives=3;
    s->frog_jump_delay_ms=100;
}

void delete_settings(Settings* s){
    /*we don't have any pointers in s now, so delete is pretty simple*/
    free(s);
}