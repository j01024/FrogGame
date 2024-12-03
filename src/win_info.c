#include "../includes/win_info.h"

void info_init(WINDOW* win_info){
    wattron(win_info, WA_BOLD);
    wmove(win_info,(WIN_INFO_HEIGHT/2)-1, WIN_INFO_PADDING + BOARD_BORDER_X);
    wprintw(win_info, "Lives");
    wmove(win_info,(WIN_INFO_HEIGHT/2)-1, (BOARD_X/3) * 1 + WIN_INFO_PADDING + BOARD_BORDER_X);
    wprintw(win_info, "Score");
    wmove(win_info,(WIN_INFO_HEIGHT/2)-1, (BOARD_X/3) * 2 + WIN_INFO_PADDING + BOARD_BORDER_X);
    wprintw(win_info, "Level");
    wattroff(win_info, WA_BOLD);
}

void info_update_score(WINDOW* win_info, int score){
    /*variables to print ideally on the middle*/
    char score_s[6]; /*that means lives can have up to 5 digits, "Score" string has 5 letters*/
    sprintf(score_s, "%d", score);
    int score_len = strlen(score_s);

    wattron(win_info, WA_BOLD);
    wmove(win_info,(WIN_INFO_HEIGHT/2), (BOARD_X/3) * 1 + WIN_INFO_PADDING + BOARD_BORDER_X + (2-score_len/2));/*2 because it is middle of "score" word"*/
    wprintw(win_info, "%s", score_s);
    wattroff(win_info, WA_BOLD);
}

void info_update_level(WINDOW* win_info, int level){
    /*variables to print ideally on the middle*/
    char level_s[6]; /*that means lives can have up to 5 digits, "Level" string has 5 letters*/
    sprintf(level_s, "%d", level);
    int level_len = strlen(level_s);

    wattron(win_info, WA_BOLD);
    wmove(win_info,(WIN_INFO_HEIGHT/2),(BOARD_X/3) * 2 + WIN_INFO_PADDING + BOARD_BORDER_X + (2-level_len/2));/*2 because it is middle of "level" word"*/
    wprintw(win_info, "%s", level_s);
    wattroff(win_info, WA_BOLD);
}

void info_update_lives(WINDOW* win_info, int lives){

    /*variables to print ideally on the middle*/
    char lives_s[6]; /*that means lives can have up to 5 digits, "Lives" string has 5 letters*/
    sprintf(lives_s, "%d", lives);
    int lives_len = strlen(lives_s);

    wattron(win_info, WA_BOLD);
    wmove(win_info,(WIN_INFO_HEIGHT/2), WIN_INFO_PADDING + BOARD_BORDER_X + (2-lives_len/2)); /*2 because it is middle of "lives word"*/
    wprintw(win_info, "%s", lives_s);
    wattroff(win_info, WA_BOLD);
}