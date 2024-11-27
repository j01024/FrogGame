#ifndef __EVENTS_H_GUARD__
#define __EVENTS_H_GUARD__
#include <stdlib.h>

/*interface containing all event functions for entity like update*/
typedef struct events{
    void (*update)(void* this); /*called every frame to update entity*/
}events;

events* new_events();

#endif