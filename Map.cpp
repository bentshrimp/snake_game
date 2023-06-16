//
// Created by user on 6/16/23.
//

#include <string>
#include <vector>
#include <fstream>
#include "ncurses.h"
#include "Map.h"

using namespace std;

Map::Map(string src) {
    ifstream file(src); // example.txt 파일을 연다. 없으면 생성.
    if(file.is_open()){
        string line;
        while(getline(file, line)) {
            m.push_back(line);
        }
        file.close(); // 열었떤 파일을 닫는다.
    }
    size = m.size();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < m[0].size(); j++){
            char c = m[i][j];
            switch (c) {
                case '1':
                    c = 'X';
                    break;
                case '2':
                    c = '*';
                    break;
                case '3':
                    c = 'O';
                    break;
                case '4':
                    c = '~';
                    break;
                default:
                    c = ' ';
            }
            mvaddch(i,j,c);
        }
    }
}
