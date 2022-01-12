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

enum TileName : uint8_t {
    WATER = 0,
    SAND,
    GROUND,
};

struct Tile {
    TileName name;
    uint8_t lightLevel;
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
    Chunk(const int x, const int y);
    ~Chunk();
    
    void Draw(const TextureAtlas& textureAtlas, const Vector2f& mapOffset);
    
    bool InWindow(const int windowStartX, const int windowStartY) const;
    
    Vector2f GetChunkPosition() const; 
    Vector2f GlobalToRelativeChunkPosition(const Vector2f& v) const;
    Vector2f RelativeToTileCoordinate(const Vector2f& v) const;
    Vector2f TileToGlobalCoordinate(const Vector2f& v) const;

    static Vector2f GlobalToChunkIndexPosition(const int x, const int y);

private:
    TileName getTileType(const int x, const int y) const;
    
    Vector2f getStartOfVisibleChunk(const Vector2f& mapOffset) const;
    Vector2f getEndOfVisibleChunk(const Vector2f& mapOffset) const;

    bool pointInWindow(const int x, const int y) const;
};

#endif /* Chunk_hpp */
