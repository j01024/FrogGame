#include "../includes/loop.h"

FrogGame* Game; /*pointer to the game i don't any better place to keep it*/


/*init all objects here*/
void init_loop(){
    init_background(); /*game requires background initalized, otherwise assertion will fail*/
    Game = new_game();  
    game_generate_background(Game);
    
    info_init(WIN_INFO);
    game_init_info(Game, WIN_INFO);
}

/*all per frame updates goes here, if you need more loops add more functions and call them inside loop()*/
void update_loop(){
    Game->events->update(Game);
    Game->drawing->draw(Game, WIN_BOARD,NULL);

    wrefresh(WIN_BOARD);
    wrefresh(WIN_INFO);
}

/*main loop maintains steady FPS and calls all specialized updates*/
void loop(){
    init_loop();
    game_draw_background(Game, WIN_BOARD);

    clock_t actual_time=0;
    clock_t previous_time=0;
    double time_delta=0;

    while(1){
        actual_time = clock();
        time_delta = (double)(actual_time - previous_time)/CLOCKS_PER_SEC;
        if(time_delta >= 1.0/GAME_SETTINGS->fps){ /*1.0 automatically casts expression to double*/
            previous_time = actual_time;
            update_loop();
        }
    }
}