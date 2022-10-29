#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_map>
#include "Random.h"
#include "Tile.h"
#include "Board.h"
#include "TextureManager.h"
using namespace std;
using namespace sf;



int main() {

    Board board;
    board.readFromFile("boards/config.cfg");

    sf::RenderWindow window(sf::VideoMode((board.numColumns)*32, (board.numRows)*32 + 100), "SFML works!");

    unordered_map<string, Texture> textures;

    int firstMove = 0;
    bool lost = false;
    bool win = false;
    bool setdebug = false;

    cout << "Flag count " << board.flagCount << endl;

    Sprite hiddenTileSprite(TextureManager::GetTexture("tile_revealed"));
    Sprite coverTileSprite(TextureManager::GetTexture("tile_hidden"));
    Sprite debugSprite(TextureManager::GetTexture("debug"));
    //Sprite digitsSprite(TextureManager::GetTexture("digits"));
    Sprite faceHappySprite(TextureManager::GetTexture("face_happy"));
    Sprite faceLoseSprite(TextureManager::GetTexture("face_lose"));
    Sprite faceWinSprite(TextureManager::GetTexture("face_win"));
    Sprite flagSprite(TextureManager::GetTexture("flag"));
    Sprite mineSprite(TextureManager::GetTexture("mine"));
    Sprite numberOneSprite(TextureManager::GetTexture("number_1"));
    Sprite numberTwoSprite(TextureManager::GetTexture("number_2"));
    Sprite numberThreeSprite(TextureManager::GetTexture("number_3"));
    Sprite numberFourSprite(TextureManager::GetTexture("number_4"));
    Sprite numberFiveSprite(TextureManager::GetTexture("number_5"));
    Sprite numberSixSprite(TextureManager::GetTexture("number_6"));
    Sprite numberSevenSprite(TextureManager::GetTexture("number_7"));
    Sprite numberEightSprite(TextureManager::GetTexture("number_8"));
    Sprite testOneSprite(TextureManager::GetTexture("test_1"));
    Sprite testTwoSprite(TextureManager::GetTexture("test_2"));
    Sprite testThreeSprite(TextureManager::GetTexture("test_3"));


    board.tiles;

    Tile tileTemp;
    for (int i = 0; i < board.numColumns; i++) {
        vector<Tile> tileTile;
        for (int j = 0; j < board.numRows; j++) {
            tileTile.push_back(tileTemp);
        }
        board.tiles.push_back(tileTile);
    }


    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                unsigned int value;
                int x;
                int y;
                Vector2<int> mousePosition = Mouse::getPosition(window);
                x = (mousePosition.x) / 32;
                y = (mousePosition.y) / 32;
                cout << x << " " << y << endl;

                if (event.key.code == Mouse::Left && x <= board.numColumns - 1 && y <= board.numRows - 1) {
                    cout << "left click" << endl;
                    cout << x << " " << y << endl;

                    if (board.tiles[x][y].isFlag)
                    {
                        board.tiles[x][y].isUnCovered = false;
                    }
                    else if (!win && !lost)
                    {
                        board.tiles[x][y].isUnCovered = true;
                        board.tilesUnCovered++;
                    }
                }
                else if (event.key.code == Mouse::Right && x <= board.numColumns - 1 && y <= board.numRows - 1)
                {
                    cout << "right click" << endl;
                    cout << x << " " << y << endl;

                    if (board.tiles[x][y].isFlag || board.tiles[x][y].isUnCovered && !win && !lost)
                    {
                        board.tiles[x][y].isFlag = false;
                        board.flagCount--;
                    }
                    else if (!win && !lost)
                    {
                        board.tiles[x][y].isFlag = true;
                        board.flagCount++;
                    }
                }
                else
                {
                    if (event.key.code == Mouse::Left && faceHappySprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        cout << x << " " << y << endl;
                        cout << "smily button hit" << endl;
                        board.resetBoard();
                        lost = false;
                        win = false;
                        board.drawRandomBoard();
                    }

                    else if (event.key.code == Mouse::Left && testOneSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                        cout << "test 1 button hit" << endl;
                        firstMove++;
                        board.resetBoard();
                        lost = false;
                        win = false;
                        board.loadTestFiles("boards/testboard1.brd");
                    }
                    else if (event.key.code == Mouse::Left && testTwoSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                        cout << "test 2 button hit" << endl;
                        firstMove++;
                        board.resetBoard();
                        lost = false;
                        win = false;
                        board.loadTestFiles("boards/testboard2.brd");
                    }
                    else if (event.key.code == Mouse::Left && testThreeSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        cout << "test 3 button hit" << endl;
                        firstMove++;
                        board.resetBoard();
                        lost = false;
                        win = false;
                        board.loadTestFiles("boards/testboard3.brd");
                    }
                    else if (event.key.code == Mouse::Left && debugSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        cout << "debug button hit" << endl;


                        for (int i = 0; i < board.numColumns; i++)
                        {
                            for (int j = 0; j < board.numRows; j++)
                            {

                                if (board.tiles[i][j].isMine)
                                {
                                    if (board.tiles[i][j].debug){
                                        board.tiles[i][j].debug = false;
                                        setdebug = false;
                                        //board.flagCount = board.setNumMines;
                                    }
                                    else {
                                        board.tiles[i][j].debug = true;
                                        setdebug = true;
                                        board.flagCount = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        window.clear();

        // draw constant images
        faceHappySprite.setPosition(((board.numColumns * 32)/2 -32), ((board.numRows) * 32));
        window.draw(faceHappySprite);

        debugSprite.setPosition(((board.numColumns * 32)/2) + 96, board.numRows * 32);
        window.draw(debugSprite);

        testOneSprite.setPosition(((board.numColumns * 32)/2) + 160, board.numRows * 32);
        window.draw(testOneSprite);

        testTwoSprite.setPosition(((board.numColumns * 32)/2) + 224, board.numRows * 32);
        window.draw(testTwoSprite);

        testThreeSprite.setPosition(((board.numColumns * 32)/2) + 288, board.numRows * 32);
        window.draw(testThreeSprite);


        // draw board loop

        for (int i = 0; i < board.numColumns; i++)
        {
            for (int j = 0; j < board.numRows; j++)
            {
                coverTileSprite.setPosition(i * 32, j * 32);
                window.draw(coverTileSprite);

                board.drawMineCounter((board.setNumMines - board.flagCount), window);

                if (firstMove == 0){
                    board.drawRandomBoard();
                    firstMove++;
                    //board.flagCount = board.setNumMines;
                }

                if (board.tiles[i][j].isUnCovered)
                {
                    //  draw unCovered tiles

                    hiddenTileSprite.setPosition(i * 32, j * 32);
                    window.draw(hiddenTileSprite);

                    board.testBombs = board.findAdjacentTiles(i,j);

                    if (board.testBombs == 1){
                        numberOneSprite.setPosition(i*32,j*32);
                        window.draw(numberOneSprite);
                    }
                    else if (board.testBombs == 2){
                        numberTwoSprite.setPosition(i*32,j*32);
                        window.draw(numberTwoSprite);
                    }
                    else if (board.testBombs == 3){
                        numberThreeSprite.setPosition(i*32,j*32);
                        window.draw(numberThreeSprite);
                    }
                    else if (board.testBombs == 4){
                        numberFourSprite.setPosition(i*32,j*32);
                        window.draw(numberFourSprite);
                    }
                    else if (board.testBombs == 5){
                        numberFiveSprite.setPosition(i*32,j*32);
                        window.draw(numberFiveSprite);
                    }
                    else if (board.testBombs == 6){
                        numberSixSprite.setPosition(i*32,j*32);
                        window.draw(numberSixSprite);
                    }
                    else if (board.testBombs == 7){
                        numberSevenSprite.setPosition(i*32,j*32);
                        window.draw(numberSevenSprite);
                    }
                    else if (board.testBombs == 8){
                        numberEightSprite.setPosition(i*32,j*32);
                        window.draw(numberEightSprite);
                    }

                    // check if mine
                    if (board.tiles[i][j].isMine && !win)
                    {
                        // draw loser face
                        lost = true;
                        faceLoseSprite.setPosition((board.numColumns * 32) / 2 - 32, (board.numRows * 32));
                        window.draw(faceLoseSprite);
                    }
                    // check if won
                    else if (board.tilesUnCovered == (board.numTiles - board.setNumMines) && !lost)
                    {

                        // draw winner face
                        win = true;
                        board.flagCount = board.setNumMines;
                        faceWinSprite.setPosition((board.numColumns * 32) / 2 - 32, (board.numRows * 32));
                        window.draw(faceWinSprite);
                    }
                    // find adjacent mines

                }
                if (board.tiles[i][j].isFlag)
                {
                    flagSprite.setPosition(i * 32, j * 32);
                    window.draw(flagSprite);
                }
                if(setdebug)
                {
                    board.debugBoard(window);
                }
                if(lost){
                    setdebug = false;
                    board.losingBoard(window);
                }
                if(win){
                    setdebug = false;
                    board.winningBoard(window);
                }
            }
        }
        window.display();
    }
    TextureManager::Clear();
    return 0;
}


