//
// Created by user on 6/16/23.
//

#include "Snake.h"
#include <vector>
#include "ncurses.h"
#include "wait.h"
#include "Map.h"
#include <string>
#include <iostream>

using namespace std;

Snake::Snake(Map map) :map(map){
    vector <string> str = map.getMap();
    for (int i = 0; i < str.size(); i++) {
        for (int j = 0; j < str[0].size(); j++) {
            if (str[i][j] == '3') {
                body.push_front(make_pair(i, j));
            } else if (str[i][j] == '4') {
                body.push_back(make_pair(i, j));
            }
        }
    }
    if (body[0].first < body[1].first) {
        dir = down;
    }
    if (body[0].first > body[1].first) {
        dir = up;
    }
    if (body[0].second < body[1].second) {
        dir = left;
    }
    if (body[0].second > body[1].second) {
        dir = right;
    }
}

void Snake::print() {
    for (int i = 0; i < body.size(); i++) {
        mvaddch(body[i].first, body[i].second, 'O');
    }
}

bool Snake::move() {
    usleep(500000);
    pair<int, int> head = body.front();
    pair<int, int> tail = body.back();
    mvaddch(tail.first, tail.second, ' ');
    body.pop_back();
    body.push_front(make_pair(head.first + dir.first, head.second + dir.second));
    if (head.first > map.getHeight() || head.first == 1 || head.second > map.getWidth() || head.second == 1){
        return true;
    } else {
        return false;
    }
}

void Snake::inputKey() {
    nodelay(stdscr, TRUE);
    int key = getch();

    switch (key) {
        case KEY_UP:
            if (dir != down) {
                dir = up;
            }
            break;
        case KEY_DOWN:
            if (dir != up) {
                dir = down;
            }
            break;
        case
            KEY_LEFT:
            if (dir != right) {
                dir = left;
            }
            break;
        case
            KEY_RIGHT:
            if (dir != left) {
                dir = right;
            }
            break;
    }
}

