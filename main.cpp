//
// Created by user on 6/17/23.
//
#include "snake_game.h"

int maxheight, maxwidth;

void Play_Game();

int Ready(int n);

int Play_Again();

void ClearCentre();

int User_Input();

string maps[] = {"map1.txt", "map2.txt"};

int main() {
    for (int i = 0; i < 3; i++) {
        if (Ready(i) == 'y') {
            snake_game NewSnake = snake_game(maps[0], 10 * (i + 1), 3 * (i + 1), i + 1);
            if (!NewSnake.Play_Game()) {
                break;
            }
        } else {
            break;
        }
    }
    printw("Clear!");
    return 0;
}

void ClearCentre(float x, float y) {
    clear(); // clear the screen if the game is played for the 2nd time
    initscr();
    noecho();
    getmaxyx(stdscr, maxheight, maxwidth);
    move((maxheight / y), (maxwidth / x));
}

// receive user confirmation
int User_Input() {
    int UserInput = getch();
    refresh();
    endwin();
    clear();

    return UserInput;
}

// print start menu
int Ready(int n) {
    ClearCentre(2.5, 2.5);
    printw("stage%d Are you ready? (y/n)", n+1);
    return User_Input();
}

// print end of the game menu and ask user to play again
int Play_Again() {
    ClearCentre(2.5, 2.5);
    printw("Do you want to play again? (y/n)");
    return User_Input();
}