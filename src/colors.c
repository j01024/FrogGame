#include "../includes/colors.h"
bool __colors_initalized=false;

chtype COLOR_DEFAULT;
chtype COLOR_FROG;

chtype COLOR_CAR_ENEMY;
chtype COLOR_CAR_FRIENDLY;
chtype COLOR_CAR_TELEPORTER;

chtype COLOR_ROAD;
chtype COLOR_PAVEMENT;
chtype COLOR_GRASS;

void init_colors(){
    init_pair(1, COLOR_RED, COLOR_BLACK); //default
    init_pair(2, COLOR_GREEN, COLOR_BLACK); //frog

    init_pair(3, COLOR_BLACK, COLOR_BLACK); //road
    init_pair(4, COLOR_BLACK, COLOR_GREEN); //grass
    init_pair(5, COLOR_BLACK, COLOR_WHITE); //pavement

    init_pair(6, COLOR_RED, COLOR_BLACK); //enemy car
    init_pair(7, COLOR_GREEN, COLOR_BLACK); //friendly car
    init_pair(8, COLOR_YELLOW, COLOR_BLACK); //teleporter car

    COLOR_DEFAULT = COLOR_PAIR(1);
    COLOR_FROG = COLOR_PAIR(2);
    
    COLOR_ROAD = COLOR_PAIR(3);
    COLOR_GRASS= COLOR_PAIR(4);
    COLOR_PAVEMENT= COLOR_PAIR(5);

    COLOR_CAR_ENEMY = COLOR_PAIR(6);
    COLOR_CAR_FRIENDLY = COLOR_PAIR(7);
    COLOR_CAR_TELEPORTER = COLOR_PAIR(8);

    __colors_initalized = true;
}