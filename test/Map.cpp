//
// Created by user on 6/16/23.
//

#include "Map.h"
#include "ncurses.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

Map::Map(string m) {
    string line;
    ifstream file(m); // example.txt 파일을 연다. 없으면 생성.
    if (file.is_open()) {
        while (getline(file, line)) {
            str.push_back(line);
        }
        file.close(); // 열었떤 파일을 닫는다.
    }
    height = str.size();
    width = str[0].size();
}

void Map::print() {
    for (int i = 0; i < str.size(); i++){
        for (int j = 0; j < str[0].size(); j++){
            char c = str[i][j];
            switch (c) {
                case '1':
                    c = 'X';
                    break;
                case '2':
                    c = '*';
                    break;
                default:
                    c = ' ';
            }
            mvaddch(i,j,c);
        }
    }
}

vector<string> Map::getMap() {
    return str;
}

int Map::getWidth() {
    return width;
}
int Map::getHeight() {
    return height;
}
