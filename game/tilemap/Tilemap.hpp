//
//  Tilemap.hpp
//  OceanGame
//
//  Created by Gabriele Padovani on 26/12/21.
//

#ifndef Tilemap_hpp
#define Tilemap_hpp

#include <stdio.h>

#include "../../engine/Engine.hpp"
#include "../../engine/Time.hpp"
#include "../../physics/Vector2f.hpp"
#include "TextureAtlas.hpp"

enum TileName {
    WATER = 0,
    SAND,
    GROUND,
};

struct Tile {
    TileName name;
    int lightLevel;
};

class Tilemap {
private:
    static const int TileSize = 24;
    
    int tileNumberX = (int)ceil(2*Engine::WINDOW_WIDTH / TileSize) + 2;
    int tileNumberY = (int)ceil(2*Engine::WINDOW_HEIGHT / TileSize) + 2;

    
    Vector2f mapOffset;
    TextureAtlas textureAtlas;
    
    Tile tiles[100][100];
    
private:
    TileName getTileType(int x, int y);
    
public:
    Tilemap();
    ~Tilemap(); 
    
    void Update();
    void Draw();
};

#endif /* Tilemap_hpp */
