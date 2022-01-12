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
#include "Chunk.hpp"

class Tilemap {
private:
    int playerSpeed = 1000;
    
    Vector2f mapOffset;
    
    TextureAtlas textureAtlas;
    
    std::vector<Chunk> chunks = std::vector<Chunk>();
    
private:
    void updateChunkList();
    
    bool chunkListContains(const Vector2f& chunkPos) const;
    bool chunkPositionInWindow(Vector2f pos);
    
    TileName getTileType(int x, int y);
    
public:
    Tilemap();
    ~Tilemap(); 
    
    void Update();
    void Draw();
};

#endif /* Tilemap_hpp */
