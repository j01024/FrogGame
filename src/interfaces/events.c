#include "../../includes/interfaces/events.h"

events *new_events(){
    events *e = (events *)malloc(sizeof(events));
    return e;
}
