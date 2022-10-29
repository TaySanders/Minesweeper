//
// Created by Taylor Sanders on 4/11/22.
//

#ifndef PROJECT_3_TILE_H
#define PROJECT_3_TILE_H
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Tile {


public:
    bool isFlag = false;
    bool isMine = false;
    bool debug = false;
    bool isUnCovered = false;
    int minesNear;

    vector<Tile*> adjacentTile;
    void recursiveReveal();

};


#endif //PROJECT_3_TILE_H
