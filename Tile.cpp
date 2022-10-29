//
// Created by Taylor Sanders on 4/11/22.
//

#include "Tile.h"
#include "Board.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
using namespace sf;




void Tile ::recursiveReveal() {
    Board board;

    if(!isUnCovered && !isFlag){
        isUnCovered = true;
        board.tilesUnCovered++;

        if(minesNear == 0 && !isMine){
            for(int c = 0; c < 8; c++){
                if(adjacentTile[c] != nullptr && !(adjacentTile[c]->isMine)){
                    adjacentTile[c]->recursiveReveal();
                }
            }
        }
    }
}





