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
    
}

void Tilemap::Draw(){
    
    for (int i = 0; i < chunks.size(); i++) {
        if (chunks[i].InWindow(mapOffset.x, mapOffset.y)){
            chunks[i].Draw(textureAtlas, mapOffset);
        }
    }
    
}
