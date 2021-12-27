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

    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            tiles[x][y] = Tile{(TileName)(rand() % 3), 10}; 
        }
    }
    
}

Tilemap::~Tilemap(){}


TileName Tilemap::getTileType(int x, int y){
    if (x < 0 || x > 100 || y < 0 || y > 100){
        return TileName::GROUND;
    }
        
    return tiles[x][y].name;
}




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
    
    for (int x = 0; x < tileNumberX; x++) {
        for (int y = 0; y < tileNumberY; y++) {
            
            SDL_Rect tileBounds = textureAtlas.GetTileDescriptor(getTileType(x, y));
            SDL_Rect tilePos = SDL_Rect{x * TileSize - (int)mapOffset.x, y * TileSize - (int)mapOffset.y, TileSize, TileSize};
            
            Engine::SetTextureColor(textureAtlas.GetTexture(),
                                    255-255*y / tileNumberY,
                                    255-255*y / tileNumberY,
                                    255-255*y / tileNumberY);
            
            Engine::RenderTexture(textureAtlas.GetTexture(), tileBounds, tilePos);
        }
    }
    
}
