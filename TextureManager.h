//
// Created by Taylor Sanders on 4/11/22.
//
#include <SFML/Graphics.hpp>
#ifndef PROJECT_3_TEXTUREMANAGER_H
#define PROJECT_3_TEXTUREMANAGER_H
#include <unordered_map>
#include <string>
using namespace std;
using namespace sf;



class TextureManager {

    static unordered_map<string, Texture> textures;
    static void LoadTexture(string textureName);

public:
    static Texture& GetTexture(string textureName);
    static void Clear();
};


#endif //PROJECT_3_TEXTUREMANAGER_H
