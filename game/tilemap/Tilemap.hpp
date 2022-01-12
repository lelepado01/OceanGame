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
    Vector2f mapOffset;
    TextureAtlas textureAtlas;
    
    std::vector<Chunk> chunks = std::vector<Chunk>();
    
private:
    TileName getTileType(int x, int y);
    
    std::vector<Vector2f> getChunksInWindow();
    bool chunkPositionInWindow(Vector2f pos);
    
public:
    Tilemap();
    ~Tilemap(); 
    
    void Update();
    void Draw();
};

#endif /* Tilemap_hpp */
