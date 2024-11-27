#include "../../includes/interfaces/position.h"

/*creates new position with given data*/
position *new_position(const short x, const short y)
{
    position *pos = (position*)malloc(sizeof(position));
    pos->x = x;
    pos->y = y;

    return pos;
}

bool is_proper_coordinate(const short int x, const short int y){
    if( x>=0 && 
        y>=0 && 
        x<=BOARD_X - (2*BOARD_BORDER_X) -1 &&  /*-1 since indexing starts from 0, don't forget about borders*/
        y<=BOARD_Y - (2*BOARD_BORDER_Y) -1)
        return true;

    return false;
}
