#include "../../includes/interfaces/drawing.h"

drawing* new_drawing(){
    drawing* d = (drawing*)malloc(sizeof(drawing));\
    return d;
}