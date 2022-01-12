//
//  Tilemap.cpp
//  OceanGame
//
//  Created by Gabriele Padovani on 26/12/21.
//

#include "Tilemap.hpp"

Tilemap::Tilemap()
: textureAtlas("/Users/gabrielepadovani/Desktop/Code/C++/OceanGame/OceanGame/assets/tileset.png"){

    textureAtlas.AddTileDescriptor(WATER, SDL_Rect{16,16,16,16});
    textureAtlas.AddTileDescriptor(SAND, SDL_Rect{0, 16, 16,16});
    textureAtlas.AddTileDescriptor(GROUND, SDL_Rect{10 * 16, 1 * 16, 16,16});
    
    chunks = std::vector<Chunk>();
    
}

Tilemap::~Tilemap(){}


void Tilemap::Update(){
    
    int speed = 1000;
    
    if (Engine::KeyIsPressed(SDLK_w)){
        mapOffset.Sub(Vector2f(0,speed * Time::DeltaTime()));
    }
    if (Engine::KeyIsPressed(SDLK_s)){
        mapOffset.Add(Vector2f(0,speed * Time::DeltaTime()));
    }
    if (Engine::KeyIsPressed(SDLK_a)){
        mapOffset.Sub(Vector2f(speed * Time::DeltaTime(),0));
    }
    if (Engine::KeyIsPressed(SDLK_d)){
        mapOffset.Add(Vector2f(speed * Time::DeltaTime(),0));
    }
    
    std::vector<Vector2f> chunksInWindow = getChunksInWindow();
    for (Vector2f chunkPosition : chunksInWindow) {
        bool contained = false;
        for (int i = 0; i < chunks.size(); i++) {
            if (chunks.at(i).GetChunkPosition() == chunkPosition){
                contained = true;
                break;
            }
        }
        if (!contained){
            chunks.push_back(Chunk(chunkPosition.x, chunkPosition.y));
        }
    }
    
}

void Tilemap::Draw(){
    
    for (Chunk chunk : chunks) {
        if (chunk.InWindow(mapOffset.x, mapOffset.y)){
            chunk.Draw(textureAtlas, mapOffset);
        }
    }
    
}


std::vector<Vector2f> Tilemap::getChunksInWindow(){
    std::vector<Vector2f> v = std::vector<Vector2f>();
    
    Vector2f mapChunkPosition = Chunk::ChunkPositionFromGlobal(mapOffset.x, mapOffset.y);
    
    for (int x = mapChunkPosition.x - 1; x < mapChunkPosition.x+2; x++) {
        for (int y = mapChunkPosition.y - 1; y < mapChunkPosition.y+2; y++) {
            v.push_back(Vector2f(x, y));
        }
    }
    
    return v;
}
