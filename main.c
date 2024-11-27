#include <ncurses.h>
#include <stdlib.h>
#include "includes/setup.h"
#include "includes/frog.h"
#include "includes/loop.h"


int main(int argc, char** argv){
    setup();
    init_colors();
    init_windows();
    refresh();

    loop();

	getch();
	endwin();

    //delete_frog(f);
 
    return 0;
}