#include "../includes/background.h"

BackgroundTile* tile_default;
BackgroundTile* tile_road;
BackgroundTile* tile_grass;
BackgroundTile* tile_pavement;
bool __background_initialized=false;

void init_background(){
    tile_default = (BackgroundTile*)malloc(sizeof(BackgroundTile));
    tile_road = (BackgroundTile*)malloc(sizeof(BackgroundTile));
    tile_grass = (BackgroundTile*)malloc(sizeof(BackgroundTile));
    tile_pavement = (BackgroundTile*)malloc(sizeof( BackgroundTile));

    tile_default->key='d';
    tile_default->color=COLOR_DEFAULT;

    tile_road->key='r';
    tile_road->color = COLOR_ROAD;

    tile_grass->key='g';
    tile_grass->color = COLOR_GRASS;

    tile_pavement->key='p';
    tile_pavement->color = COLOR_PAVEMENT;

    __background_initialized = true;
}

Background* new_background(int width, int height){
    assert(width > 0 && height > 0);

    Background* bg = (Background*)malloc(sizeof(Background));
    bg->width = width;
    bg->height = height;

    bg->tiles = (BackgroundTile***)malloc(sizeof(BackgroundTile**) * height);
    for(int i=0;i<height;i++)
        bg->tiles[i]=(BackgroundTile**)malloc(sizeof(BackgroundTile*) * width);

    return bg;
}

void fill_background(Background* bg, BackgroundTile* tile){
    for(int x =0;x<bg->height;x++){
        for(int y =0;y<bg->width;y++)
            bg->tiles[x][y] = tile;
    }
}

void draw_background(Background* bg, WINDOW* win){
    assert(bg!=NULL);
    assert(win!=NULL);

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

void delete_background(Background* bg){
    assert(bg!=NULL);

    for(int i=0;i<bg->height;i++)
        free(bg->tiles[i]);

    free(bg->tiles);
    free(bg);
}

BackgroundTile* get_random_tile(){
    int r = rand_in_range(0,2); /*currently there are 3 tiles*/

    switch (r)
    {
    case 0: return tile_grass;
    case 1: return tile_pavement;
    case 2: return tile_road;
    default:return tile_grass;
    }

}

void background_fill_area(Background* bg, int x, int y, int width, int height, BackgroundTile *tile){
    for(int xx=0;xx<height;xx++){
        for(int yy=0;yy<width;yy++)
            bg->tiles[xx+y][yy+x] = tile;
    }
}