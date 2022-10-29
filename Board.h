//
// Created by Taylor Sanders on 4/11/22.
//
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
#include "Tile.h"
#ifndef PROJECT_3_BOARD_H
#define PROJECT_3_BOARD_H
using namespace std;
using namespace sf;


class Board {
public:

    vector <vector<Tile>> tiles;
    int numColumns;
    int numRows;
    int setNumMines;
    int numMines;
    int flagCount = 0;
    int numTiles;
    int testBombs;
    int numBombs = 0;
    int tilesUnCovered = 0;
    void readFromFile(string filename);
    void loadTestFiles(string filename);
    void drawRandomBoard();
    void drawMineCounter(int value, RenderWindow &window);
    void resetBoard();
    void losingBoard(RenderWindow &window);
    void winningBoard(RenderWindow &window);
    void debugBoard(RenderWindow &window);
    int findAdjacentTiles(int i, int j);


};


#endif //PROJECT_3_BOARD_H
