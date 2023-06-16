//
// Created by user on 6/17/23.
//
#include "snake_game.h"

int maxheight, maxwidth;
void Play_Game();
int Ready();
int Play_Again();
void ClearCentre();
int User_Input();

int main(){
    if(Ready() == 'y')
        do {
            snake_game NewSnake = snake_game("map.txt");
            NewSnake.Play_Game();
        }
        while(Play_Again() == 'y');
    return 0;
}

void ClearCentre(float x, float y)
{
    clear(); // clear the screen if the game is played for the 2nd time
    initscr();
    noecho();
    getmaxyx(stdscr, maxheight, maxwidth);
    move((maxheight/y), (maxwidth/x));
}

// receive user confirmation
int User_Input()
{
    int UserInput = getch();
    refresh();
    endwin();
    clear();

    return UserInput;
}

// print start menu
int Ready()
{
    ClearCentre(2.5, 2.5);
    printw("Welcome to the Snake Game. Are you ready? (y/n)");
    return User_Input();
}

// print end of the game menu and ask user to play again
int Play_Again()
{
    ClearCentre(2.5, 2.5);
    printw("Do you want to play again? (y/n)");
    return User_Input();
}