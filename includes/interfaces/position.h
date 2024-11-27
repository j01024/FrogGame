#ifndef __position_H_GUARD__
#define __position_H_GUARD__
#include "../setup.h"
#include <ncurses.h>
#include <stdlib.h>

/*position class is interface for all entites that are drawable and have position. It should not be used externally*/
typedef struct position
{
    short x;
    short y;
}position;

/*creates new position with given data*/
position *new_position(const short x, const short y);
/*returns true if given point is proper on board coordinate, false if not*/
bool is_proper_coordinate(const short x, const short y);

#endif