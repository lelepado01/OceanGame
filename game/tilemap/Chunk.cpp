//
//  Chunk.cpp
//  OceanGame
//
//  Created by Gabriele Padovani on 27/12/21.
//

#include "Chunk.hpp"

Chunk::Chunk(int x, int y){
    chunkPositionX = x;
    chunkPositionY = y;
    
    globalChunkPositionX = chunkPositionX * ChunkSize;
    globalChunkPositionY = chunkPositionY * ChunkSize;
    
    chunkRectangle = {globalChunkPositionX, globalChunkPositionY, ChunkSize, ChunkSize};
    
    for (int x = 0; x < TileNumber; x++) {
        for (int y = 0; y < TileNumber; y++) {
            tiles[x][y] = Tile{(TileName)(rand() % 3), 10};
        }
    }
}

Chunk::~Chunk(){}

TileName Chunk::getTileType(int x, int y){
    if (x < 0 || x >= TileNumber || y < 0 || y >= TileNumber){
        return TileName::GROUND;
    }
        
    return tiles[x][y].name;
}


void Chunk::Draw(const TextureAtlas& textureAtlas, const Vector2f& mapOffset){
    for (int x = 0; x < TileNumber; x++) {
        for (int y = 0; y < TileNumber; y++) {
            
            int relativePosX = x * TileSize + globalChunkPositionX - (int)mapOffset.x;
            int relativePosY = y * TileSize + globalChunkPositionY - (int)mapOffset.y;
            
            SDL_Rect tileBounds = textureAtlas.GetTileDescriptor(getTileType(x, y));
            SDL_Rect tilePos = SDL_Rect{relativePosX, relativePosY, TileSize, TileSize};
            
            Engine::SetTextureColor(textureAtlas.GetTexture(),
                                    255-255*y / TileNumber,
                                    255-255*y / TileNumber,
                                    255-255*y / TileNumber);
            
            Engine::RenderTexture(textureAtlas.GetTexture(), tileBounds, tilePos);
        }
    }
}

Vector2f Chunk::GetChunkPosition(){
    return Vector2f(chunkPositionX, chunkPositionY);
}

bool Chunk::InWindow(int windowStartX, int windowStartY){
    SDL_Rect window {windowStartX, windowStartY, Engine::WINDOW_WIDTH * 2, Engine::WINDOW_HEIGHT * 2};
    SDL_Rect res;
    return SDL_IntersectRect(&window, &chunkRectangle, &res) == SDL_TRUE;
}

Vector2f Chunk::ChunkPositionFromGlobal(int x, int y){
    Vector2f v(x, y);
    v.x = floor(v.x / ChunkSize);
    v.y = floor(v.y / ChunkSize);
    return  v;
}
