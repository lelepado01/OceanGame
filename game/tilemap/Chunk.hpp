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
public:
    static const int TileNumber = 100;
    static const int TileSize = 24;
    static const int ChunkSize = TileNumber * TileSize;
    
private:
    int chunkPositionX;
    int chunkPositionY;
    
    SDL_Rect chunkRectangle;

    Tile tiles[TileNumber][TileNumber];
    
public:
    Chunk(int x, int y);
    ~Chunk();
    
    void Draw(const TextureAtlas& textureAtlas, const Vector2f& mapOffset);
    
    bool InWindow(int offX, int offY);
    
    Vector2f GetChunkPosition(); 
    Vector2f GlobalToRelativeChunkPosition(Vector2f v);
    Vector2f RelativeToTileCoordinate(Vector2f v);

    static Vector2f GlobalToChunkIndexPosition(int x, int y);

private:
    TileName getTileType(int x, int y);
    
//    Vector2f getStartOfVisibleChunk();
//    Vector2f getEndOfVisibleChunk();

    bool pointInWindow(int x, int y);
};

#endif /* Chunk_hpp */
