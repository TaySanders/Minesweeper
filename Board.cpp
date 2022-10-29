//
// Created by Taylor Sanders on 4/11/22.
//

#include "Board.h"
#include "Tile.h"
#include "Random.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
using namespace sf;


void Board :: readFromFile(string filename) {
    ifstream inputFile(filename);

    if (inputFile.is_open()) {

        inputFile >> numColumns;
        inputFile >> numRows;
        inputFile >> numMines;

        numTiles = numColumns * numRows;

        cout << numColumns << endl;
        cout << numRows << endl;
        cout << numMines << endl;
        cout << numTiles << endl;
    }
}

void Board:: loadTestFiles(string filename) {
    Sprite mineSprite(TextureManager::GetTexture("mine"));

    ifstream loadMines(filename);
    string fileData;
    string holdMines;

    while (getline(loadMines, fileData))
    {
        holdMines += fileData;
    }

    for (int k = 0; k < holdMines.size(); k++)
    {
        int y = k / numColumns;
        int x = k % numColumns;
        if (holdMines.at(k) == '1') {
            tiles[x][y].isMine = true;
            setNumMines++;
        }
    }
}

void Board:: drawRandomBoard() {
    for (int i = 0; i < numMines; i++) {

        int xpos = Random::Int(0, numColumns - 1);
        int ypos = Random::Int(0, numRows - 1);

        if (tiles[xpos][ypos].isMine) {
            i--;
        } else {
            tiles[xpos][ypos].isMine = true;
        }
    }
    setNumMines = numMines;
}
void Board :: debugBoard(RenderWindow &window){
    Sprite mineSprite(TextureManager::GetTexture("mine"));

    for (unsigned int a = 0; a < numColumns; a++)
    {
        for (unsigned int b = 0; b < numRows; b++)
        {
            // if mine, loop through and draw every mine
            if (tiles[a][b].isMine)
            {
                mineSprite.setPosition(a * 32, b * 32);
                window.draw(mineSprite);
            }
        }
    }
}
void Board :: losingBoard(RenderWindow &window){
    Sprite mineSprite(TextureManager::GetTexture("mine"));
    Sprite hiddenTileSprite(TextureManager::GetTexture("tile_revealed"));

    for (unsigned int a = 0; a < numColumns; a++)
    {
        for (unsigned int b = 0; b < numRows; b++)
        {
            // if mine, loop through and draw every mine
            if (tiles[a][b].isMine)
            {
                hiddenTileSprite.setPosition(a * 32, b * 32);
                window.draw(hiddenTileSprite);
                mineSprite.setPosition(a * 32, b * 32);
                window.draw(mineSprite);

            }
        }
    }
}

void Board ::  winningBoard(RenderWindow &window){
    Sprite flagSprite(TextureManager::GetTexture("flag"));
    for (int a = 0; a < numColumns; a++)
    {
        for (int b = 0; b < numRows; b++)
        {
            // if mine, loop through and draw every mine
            if (tiles[a][b].isMine)
            {
                flagSprite.setPosition(a * 32, b * 32);
                window.draw(flagSprite);
                //flagCount++;
            }
        }
    }
}

void Board :: drawMineCounter(int value, RenderWindow &window){
    // mine counter
    bool negative = false;

    if (value < 0){
        value = value * -1;
        negative = true;
    }
    Sprite thousands(TextureManager::GetTexture("digits"));
    thousands.setTextureRect(Rect<int>(21*10, 0, 21,32));
    thousands.setPosition(0, numRows*32);
    Sprite hundreds(TextureManager::GetTexture("digits"));
    hundreds.setTextureRect(Rect<int>(0,0,21,32));
    hundreds.setPosition(0, numRows*32);
    Sprite tens(TextureManager::GetTexture("digits"));
    tens.setTextureRect(Rect<int>(21*5,0,21,32));
    tens.setPosition(21, numRows*32);
    Sprite ones(TextureManager::GetTexture("digits"));
    ones.setTextureRect(Rect<int>(0,0,21,32));
    ones.setPosition(42,numRows * 32);

    int copy = value;
    int onesPlace = copy % 10;
    copy/= 10;
    int tensPlace = copy % 10;
    int hundredsPlace = copy/10;

    hundreds.setTextureRect(Rect<int>(21*hundredsPlace,0,21,32));
    tens.setTextureRect(Rect<int>(21*tensPlace,0,21,32));
    ones.setTextureRect(Rect<int>(21*onesPlace,0,21,32));

    if(negative){
        thousands.setPosition(0,numRows*32);
        hundreds.setPosition(21, numRows*32);
        tens.setPosition(42, numRows*32);
        ones.setPosition(63,numRows * 32);
        window.draw(thousands);
        window.draw(hundreds);
        window.draw(tens);
        window.draw(ones);
    }
    else {
        window.draw(hundreds);
        window.draw(tens);
        window.draw(ones);
    }
}



void Board :: resetBoard(){
    for (int i = 0; i < numColumns; i++)
    {
        for (int j = 0; j < numRows; j++)
        {
            tiles[i][j].isFlag = false;
            tiles[i][j].isUnCovered = false;
            tiles[i][j].isMine = false;
            tiles[i][j].debug = false;
            tilesUnCovered = 0;
            flagCount = 0;
            setNumMines = 0;
        }
    }
}

int Board :: findAdjacentTiles(int i, int j) {

    numBombs = 0;

    tiles[i][j].adjacentTile.clear();

    for (int k = 0; k < 8; k++) {
        tiles[i][j].adjacentTile.push_back(nullptr);
    }

    if (i == 0 && j == 0) //tile is top left corner
    {

        tiles[i][j].adjacentTile[4] = &(tiles[i + 1][j]);
        tiles[i][j].adjacentTile[6] = &(tiles[i][j + 1]);
        tiles[i][j].adjacentTile[7] = &(tiles[i + 1][j + 1]);

        if (tiles[i + 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i][j - 1].isMine) {
            numBombs++;
        }
        if (tiles[i + 1][j + 1].isMine) {
            numBombs++;
        }
    }
    else if (i == numColumns - 1 && j == 0) // tile is top right corner
    {

        tiles[i][j].adjacentTile[3] = &(tiles[i - 1][j]);
        tiles[i][j].adjacentTile[6] = &(tiles[i][j + 1]);
        tiles[i][j].adjacentTile[5] = &(tiles[i - 1][j + 1]);

        if (tiles[i - 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i][j + 1].isMine) {
            numBombs++;
        }
        if (tiles[i - 1][j + 1].isMine) {
            numBombs++;
        }
    }
    else if (i == 0 && j == numRows - 1) // tile is bottom left corner
    {

        tiles[i][j].adjacentTile[4] = &(tiles[i + 1][j]);
        tiles[i][j].adjacentTile[1] = &(tiles[i][j - 1]);
        tiles[i][j].adjacentTile[2] = &(tiles[i + 1][j - 1]);

        if (tiles[i + 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i][j - 1].isMine) {
            numBombs++;
        }
        if (tiles[i + 1][j - 1].isMine) {
            numBombs++;
        }
    }
    else if (i == numColumns - 1 && j == numRows - 1) // tile is bottom right corner
    {

        tiles[i][j].adjacentTile[3] = &(tiles[i - 1][j]);
        tiles[i][j].adjacentTile[1] = &(tiles[i][j - 1]);
        tiles[i][j].adjacentTile[0] = &(tiles[i - 1][j - 1]);

        if (tiles[i - 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i][j - 1].isMine) {
            numBombs++;
        }
        if (tiles[i - 1][j - 1].isMine) {
            numBombs++;
        }
    }
    else if (i < numColumns && j == 0) // tile is on the top
    {

        tiles[i][j].adjacentTile[3] = &(tiles[i - 1][j]);
        tiles[i][j].adjacentTile[4] = &(tiles[i + 1][j]);
        tiles[i][j].adjacentTile[5] = &(tiles[i - 1][j + 1]);
        tiles[i][j].adjacentTile[6] = &(tiles[i][j + 1]);
        tiles[i][j].adjacentTile[7] = &(tiles[i + 1][j + 1]);

        if (tiles[i - 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i + 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i - 1][j + 1].isMine) {
            numBombs++;
        }
        if (tiles[i][j + 1].isMine) {
            numBombs++;
        }
        if (tiles[i + 1][j + 1].isMine) {
            numBombs++;
        }
    }
    else if (i < numColumns && j == numRows - 1) // tile is on the bottom
    {

        tiles[i][j].adjacentTile[3] = &(tiles[i - 1][j]);
        tiles[i][j].adjacentTile[4] = &(tiles[i + 1][j]);
        tiles[i][j].adjacentTile[2] = &(tiles[i + 1][j - 1]);
        tiles[i][j].adjacentTile[1] = &(tiles[i][j - 1]);
        tiles[i][j].adjacentTile[0] = &(tiles[i - 1][j - 1]);

        if (tiles[i - 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i + 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i + 1][j - 1].isMine) {
            numBombs++;
        }
        if (tiles[i][j - 1].isMine) {
            numBombs++;
        }
        if (tiles[i - 1][j - 1].isMine) {
            numBombs++;
        }
    }
    else if (i == 0) // tile on left edge
    {

        tiles[i][j].adjacentTile[4] = &(tiles[i + 1][j]);
        tiles[i][j].adjacentTile[6] = &(tiles[i][j + 1]);
        tiles[i][j].adjacentTile[7] = &(tiles[i + 1][j + 1]);
        tiles[i][j].adjacentTile[1] = &(tiles[i][j - 1]);
        tiles[i][j].adjacentTile[2] = &(tiles[i + 1][j - 1]);

        if (tiles[i + 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i][j + 1].isMine) {
            numBombs++;
        }
        if (tiles[i + 1][j + 1].isMine) {
            numBombs++;
        }
        if (tiles[i][j - 1].isMine) {
            numBombs++;
        }
        if (tiles[i + 1][j - 1].isMine) {
            numBombs++;
        }
    }
    else if (i == numColumns - 1) // tile is on the right edge
    {
        tiles[i][j].adjacentTile[3] = &(tiles[i - 1][j]);
        tiles[i][j].adjacentTile[0] = &(tiles[i - 1][j - 1]);
        tiles[i][j].adjacentTile[1] = &(tiles[i][j - 1]);
        tiles[i][j].adjacentTile[5] = &(tiles[i - 1][j + 1]);
        tiles[i][j].adjacentTile[6] = &(tiles[i][j + 1]);

        if (tiles[i - 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i - 1][j - 1].isMine) {
            numBombs++;
        }
        if (tiles[i][j - 1].isMine) {
            numBombs++;
        }
        if (tiles[i - 1][j + 1].isMine) {
            numBombs++;
        }
        if (tiles[i][j + 1].isMine) {
            numBombs++;
        }
    }
    else // tile is in the middle
    {

        tiles[i][j].adjacentTile[3] = &(tiles[i - 1][j]);
        tiles[i][j].adjacentTile[4] = &(tiles[i + 1][j]);
        tiles[i][j].adjacentTile[5] = &(tiles[i - 1][j + 1]);
        tiles[i][j].adjacentTile[6] = &(tiles[i][j + 1]);
        tiles[i][j].adjacentTile[7] = &(tiles[i + 1][j + 1]);
        tiles[i][j].adjacentTile[2] = &(tiles[i + 1][j - 1]);
        tiles[i][j].adjacentTile[1] = &(tiles[i][j - 1]);
        tiles[i][j].adjacentTile[0] = &(tiles[i - 1][j - 1]);

        if (tiles[i - 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i + 1][j].isMine) {
            numBombs++;
        }
        if (tiles[i - 1][j + 1].isMine) {
            numBombs++;
        }
        if (tiles[i][j + 1].isMine) {
            numBombs++;
        }
        if (tiles[i + 1][j + 1].isMine) {
            numBombs++;
        }
        if (tiles[i + 1][j - 1].isMine) {
            numBombs++;
        }
        if (tiles[i][j - 1].isMine) {
            numBombs++;
        }
        if (tiles[i - 1][j - 1].isMine) {
            numBombs++;
        }
    }


    tiles[i][j].minesNear = numBombs;

    //if(tiles[i][j].minesNear == 0){
      // tiles[i][j].recursiveReveal();
    //}

    return numBombs;
}

