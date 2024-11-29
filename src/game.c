#include "../includes/game.h"

FrogGame* Game;
void init_game()
{
    init_background();
    Game = (FrogGame*)malloc(sizeof(FrogGame));
    Game->background = new_background(BOARD_X-BOARD_BORDER_X*2,BOARD_Y-BOARD_BORDER_Y*2); /*border is from 2 sides*/
    Game->frog = new_frog(BOARD_X/2,BOARD_Y - 2*BOARD_BORDER_Y - 1);/*middle bottom of board, minus 2 times border -1, to match 0 indexing*/

    Game->events = new_events();
    Game->events->update= game_update;

    Game->drawing = new_drawing();
    Game->drawing->draw=game_draw;

    Game->cars = (Car**)malloc(sizeof(Car*) * CARS_INITIAL_SIZE);
    Game->__cars_num=0;
    Game->__cars_size=CARS_INITIAL_SIZE;

    fill_background(Game->background, tile_default); /*fill background with default tile to prevent frustrating null errors when you forget about it*/
}
FrogGame* new_game()
{
    assert(__background_initialized && "Background has not been initialized, use init_background in your setup to initialize");
    FrogGame* game = (FrogGame*)malloc(sizeof(FrogGame));
    game->background = new_background(BOARD_X-BOARD_BORDER_X*2,BOARD_Y-BOARD_BORDER_Y*2); /*border is from 2 sides*/
    game->frog = new_frog(BOARD_X/2,BOARD_Y - BOARD_BORDER_Y); /*middle bottom of board*/
    fill_background(Game->background, tile_default); /*fill background with default tile to prevent frustrating null errors, when you forget about it*/

    game->events = new_events();
    game->events->update= game_update;

    game->drawing = new_drawing();
    game->drawing->draw=game_draw;

    game->cars = (Car**)malloc(sizeof(Car*) * CARS_INITIAL_SIZE);
    game->__cars_num=0;
    game->__cars_size=CARS_INITIAL_SIZE;

    return game;
}

void game_update(void* this){
    FrogGame* game = (FrogGame*)this;
    Frog* frog = game->frog;

    frog->events->update(game->frog);
    for(int i=0;i<game->__cars_num;i++){
        Car* c = game->cars[i];
        c->events->update(game->cars[i]);

        /*check car collisions with frog*/
        if(c->frog_collision(c)){
            switch(c->car_type){
                case CAR_FRIENDLY:
                    frog->friendly_car_collision(frog);
                    break;
                case CAR_ENEMY:
                    frog->enemy_car_collision(frog);
                    break;
                case CAR_TELEPORTER:
                    frog->teleporter_car_collision(frog);
                    break;
                default: break;
            }
        } 
    }
}

void game_draw_background(FrogGame* game, WINDOW* win){
    assert(game!=NULL);
    assert(win!=NULL);
    Background* bg = game->background;
    assert(bg!=NULL);

    wmove(win, BOARD_BORDER_X,BOARD_BORDER_Y);

    for(int x=0;x<bg->height;x++){
        for(int y=0;y<bg->width;y++){
            wattron(win, bg->tiles[x][y]->color);
            waddch(win, ' ');
            wattroff(win, bg->tiles[x][y]->color);
        }

        wmove(win, x+2*BOARD_BORDER_Y,BOARD_BORDER_X); /*move to the next line*/
    }

    wrefresh(win);
}

void game_generate_background(FrogGame* game){
    assert(game!=NULL);
    Background* bg = game->background;

    /*top is always grass, since level ends here, and bottom should be always pavement (you can change to grass) cause frog spawns here, and we don't want instant death*/
    background_fill_area(bg,0,0,bg->width,1, tile_grass); //top is grass

    BackgroundTile* previous_tile=NULL;
    for(int x=1;x<bg->height-1;x++){
        BackgroundTile* random_tile = get_random_tile();
        if(previous_tile != tile_road && random_tile !=tile_road)
            random_tile = tile_road; /*this prevents multiple layers of grass or pavement from spawning*/

        previous_tile = random_tile;

        /*put cars on the lane*/
        if(random_tile==tile_road){
            int cars_on_lane = rand_in_range(LANE_CARS_MIN, LANE_CARS_MAX);
            int x_offset = BOARD_X / cars_on_lane; /*offset applied so cars will spawn uniformly on the lane*/
            for(int y =0;y<cars_on_lane;y++){
                Car* c = new_random_car(x_offset*y,x, game->frog);
                add_car(Game, c);
            }
        }

        background_fill_area(bg, 0,x,bg->width,1, random_tile);
    }

    background_fill_area(bg,0,bg->height-1,bg->width,1, tile_pavement);//bottom is pavement
}

void game_draw(void* this, WINDOW* win, void* additional_data){
    FrogGame* game = (FrogGame*)this;
    game_draw_background(game,win);
    game->frog->drawing->draw(game->frog, win, game->background);

    for(int i=0;i<game->__cars_num;i++)
        game->cars[i]->drawing->draw(game->cars[i], win,game->background);
}

void add_car(FrogGame* game,Car* car){
    if(game->__cars_num >= game->__cars_size)
        __cars_resize(game, game->__cars_size*2);
    
    game->cars[game->__cars_num++]=car;
}

void __cars_resize(FrogGame* game, int new_size){
    assert(new_size > 0 && "Size cannot be negative nor zero");
    Car** copy = (Car**)malloc(sizeof(Car*) * game->__cars_num);

    for(int i=0;i<game->__cars_num;i++)
        copy[i]=game->cars[i];
    
    free(game->cars);
    game->cars = (Car**)malloc(sizeof(Car*) * new_size);

    game->__cars_size = new_size;
    if(game->__cars_num > new_size){ /*if previous car number was greater, then we lost some of the records and car number has to be updated*/
        for(int i=new_size-1;i<game->__cars_num;i++)
            delete_car(copy[i]); /*delete additional cars, otherwise we will have memory leaks*/
        game->__cars_num=new_size; /*set num to new size*/
    }

    for(int i=0;i<game->__cars_num;i++)
        game->cars[i] = copy[i];

    free(copy); /*delete copy*/
}

void __cars_clear(FrogGame* game){
    for(int i=0;i<game->__cars_num;i++)
        delete_car(game->cars[i]);
    
    free(game->cars);
    game->cars = (Car**)malloc(sizeof(Car*) * CARS_INITIAL_SIZE);
    game->__cars_num=0;
    game->__cars_size = CARS_INITIAL_SIZE;
}

void delete_game(FrogGame* game)
{
    assert(game!=NULL);

    delete_background(game->background);
    delete_frog(game->frog);
    free(game);
}
