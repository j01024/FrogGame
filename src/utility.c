#include "../includes/utility.h"
int rand_in_range(int min, int max){
    return rand() % (max + 1 - min) + min;
}

bool dice_roll(double percent_chance){
    double roll = ((double)rand() /RAND_MAX) * 100; /*number will be double in range 0 to 100*/
    if(roll <= percent_chance)
        return true;

    return false;
}