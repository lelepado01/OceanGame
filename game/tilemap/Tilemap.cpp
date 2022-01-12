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
        
    if (Engine::KeyIsPressed(SDLK_w)){
        mapOffset.Sub(Vector2f(0,playerSpeed * Time::DeltaTime()));
    }
    if (Engine::KeyIsPressed(SDLK_s)){
        mapOffset.Add(Vector2f(0,playerSpeed * Time::DeltaTime()));
    }
    if (Engine::KeyIsPressed(SDLK_a)){
        mapOffset.Sub(Vector2f(playerSpeed * Time::DeltaTime(),0));
    }
    if (Engine::KeyIsPressed(SDLK_d)){
        mapOffset.Add(Vector2f(playerSpeed * Time::DeltaTime(),0));
    }
        
    updateChunkList();
}

void Tilemap::Draw(){
    
    for (Chunk chunk : chunks) {
        if (chunk.InWindow(mapOffset.x, mapOffset.y)){
            chunk.Draw(textureAtlas, mapOffset);
        }
    }
    
}

bool Tilemap::chunkListContains(const Vector2f &chunkPos) const {
    bool contained = false;
    for (int i = 0; i < chunks.size(); i++) {
        if (chunks.at(i).GetChunkPosition() == chunkPos){
            contained = true;
            break;
        }
    }
    
    return contained;
}

void Tilemap::updateChunkList() {
    Vector2f playerChunkPosition = Chunk::GlobalToChunkIndexPosition(mapOffset.x+1, mapOffset.y+1);
    
    for (int x = playerChunkPosition.x - 1; x < playerChunkPosition.x+2; x++) {
        for (int y = playerChunkPosition.y - 1; y < playerChunkPosition.y+2; y++) {
            Vector2f chunkPosition(x, y);
            if (!chunkListContains(chunkPosition)){
                chunks.push_back(Chunk(chunkPosition.x, chunkPosition.y));
            }
        }
    }

}
