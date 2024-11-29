#ifndef __UTILITY_H_GUARD__
#define __UTILITY_H_GUARD
#include <stdlib.h> /*rand()*/
#include "background.h"

int rand_in_range(int min, int max); /*returns random number in given range <min, max>*/
bool dice_roll(double percent_chance); /*returns true if roll was succesfull*/
#endif