#ifndef __UTILITY_H_GUARD__
#define __UTILITY_H_GUARD
#include <stdlib.h> /*rand()*/
#include "background.h"


/*swaps 2 values of any type*/
 #define SWAP(x,y)        \
   typeof(x) tmp = x;     \
   x =  y;                \
   y = tmp;               \

int rand_in_range(int min, int max); /*returns random number in given range <min, max>*/
bool dice_roll(double percent_chance); /*returns true if roll was succesfull*/
int* random_sample_int(int min, int max, int count); /*returns array of random values in given range, without duplicates in range <min,max>*/
#endif