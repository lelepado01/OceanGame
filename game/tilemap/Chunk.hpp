//
//  Chunk.hpp
//  OceanGame
//
//  Created by Gabriele Padovani on 27/12/21.
//

#ifndef Chunk_hpp
#define Chunk_hpp

#include <stdio.h>

#include "../../engine/Engine.hpp"
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

class Chunk {
private:
    static const int TileNumber = 100;
    static const int TileSize = 24;

    inline static int TileNumberX = (int)ceil(2*Engine::WINDOW_WIDTH / TileSize) + 2;
    inline static int TileNumberY = (int)ceil(2*Engine::WINDOW_HEIGHT / TileSize) + 2;
    
    int offsetX;
    int offsetY;
    
    Tile tiles[TileNumber][TileNumber]; 
    
private:
    TileName getTileType(int x, int y);
    bool pointInWindow(int x, int y);
    
public:
    Chunk(int x, int y);
    ~Chunk();
    
    void Draw(const TextureAtlas& textureAtlas, const Vector2f& mapOffset);
    
    bool InWindow(int offX, int offY);
    
    static SDL_Point ToChunkPosition(SDL_Point& point); 
};

#endif /* Chunk_hpp */