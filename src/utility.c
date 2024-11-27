#include "../includes/utility.h"
int rand_in_range(int min, int max){
    return rand() % (max + 1 - min) + min;
}