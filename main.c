#include "includes/setup.h"
#include "includes/loop.h"


int main(int argc, char** argv){
    Settings* s = NULL;
    if(argc>=2)
        s = load_from_file(argv[1]); /*if file does not exists, nothing happens it will be null, default settings will be applied*/

    setup(s);
    init_colors();
    init_windows();
    refresh();

    loop();

	endwin();
    return 0;
}