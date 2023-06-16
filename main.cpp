#include <iostream>
#include "ncurses.h"
#include "Map.h"

using namespace std;

int main(){
    initscr();
    refresh();
    Map map("map.txt");
    getch();
    endwin();
    return 0;
}