//
// Created by user on 6/16/23.
//
#include <iostream>
#include "ncurses.h"
#include "Map.h"
#include "wait.h"
#include "Snake.h"

int main(){
    initscr();
    keypad(stdscr, TRUE);
    Map map = Map("map.txt");
    map.print();
    Snake snake = Snake(map);
    while(1){
        snake.print();
        snake.inputKey();
        snake.move();
        refresh();
    }
    endwin();
    return 0;
}