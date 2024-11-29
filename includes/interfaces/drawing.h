#ifndef __DRAWING_H_GUARD__
#define __DRAWING_H_GUARD__
#include <ncurses.h>
#include <stdlib.h>

/*interface containing all drawing functions for enitity*/
typedef struct drawing_t{
    void (*draw)(void* this, WINDOW* win, void* additional_data); /*draws this entity on given window, additional data hould be array of pointers or pointer to additional data (like game background data)*/
}drawing;

drawing* new_drawing();

#endif