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


int* random_sample_int(int min, int max, int count){
    assert(max-min > count && "Count has to be greater than max-min");

    int num_count = (max-min); /*+1 to create <min,max> range*/
    int* all=malloc(sizeof(int)*num_count); /*create array with all possible numbers*/
    int* out = malloc(sizeof(int)*count);
    for(int i=0;i<num_count;i++)
        all[i] = min + i;

    /*generate random permutation of array*/
    for(int x=0;x<num_count;x++){
        int i1 = rand_in_range(0, num_count);
        int i2=  rand_in_range(0, num_count);
        /*we have to use i1, i2, othweriwse macro will call rand_in_range 3 times, which is pretty bad*/
        SWAP(all[i1], all[i2]);
    }

    for(int x =0;x<count;x++)
        out[x] = all[x];

    free(all); /*free memory*/
    return out;
}