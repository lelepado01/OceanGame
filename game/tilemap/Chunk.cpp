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
    
    chunkRectangle = {chunkPositionX*ChunkSize, chunkPositionY*ChunkSize, ChunkSize, ChunkSize};
    
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
  
    Vector2f drawStart(fmax(chunkRectangle.x, mapOffset.x),
                       fmax(chunkRectangle.y, mapOffset.y));
    drawStart = RelativeToTileCoordinate(GlobalToRelativeChunkPosition(drawStart));
    
    Vector2f endOfWindow(mapOffset.x + Engine::GetWindowWidth(),
                         mapOffset.y + Engine::GetWindowHeight());
    
    Vector2f drawEnd(fmin(chunkRectangle.x + ChunkSize, endOfWindow.x),
                     fmin(chunkRectangle.y + ChunkSize, endOfWindow.y));
    drawEnd = RelativeToTileCoordinate(GlobalToRelativeChunkPosition(drawEnd));
    
    if ( drawStart.y > 0) drawStart.y -= 1;
    if ( drawStart.x > 0) drawStart.x -= 1;

    for (int y = drawStart.y; y < drawEnd.y; y++) {
        for (int x = drawStart.x; x < drawEnd.x; x++) {
            
            int relativePosX = x * TileSize + chunkRectangle.x - (int)mapOffset.x;
            int relativePosY = y * TileSize + chunkRectangle.y - (int)mapOffset.y;
            
            SDL_Rect tileBounds = textureAtlas.GetTileDescriptor(getTileType(x, y));
            SDL_Rect tilePos = SDL_Rect{relativePosX, relativePosY, TileSize, TileSize};
            
            Engine::RenderTexture(textureAtlas.GetTexture(), tileBounds, tilePos);
        }
        
        Engine::SetTextureColor(textureAtlas.GetTexture(),
                                255-255*y / TileNumber,
                                255-255*y / TileNumber,
                                255-255*y / TileNumber);
    }
}

Vector2f Chunk::GetChunkPosition(){
    return Vector2f(chunkPositionX, chunkPositionY);
}

bool Chunk::InWindow(int windowStartX, int windowStartY){
    SDL_Rect window {windowStartX, windowStartY, Engine::GetWindowWidth(), Engine::GetWindowHeight()};
    SDL_Rect res;
    return SDL_IntersectRect(&window, &chunkRectangle, &res) == SDL_TRUE;
}

Vector2f Chunk::GlobalToRelativeChunkPosition(Vector2f v){
    v.Sub(Vector2f(chunkRectangle.x, chunkRectangle.y));
    return v;
}

Vector2f Chunk::RelativeToTileCoordinate(Vector2f v){
    v.Div(TileSize);
    return v;
}

Vector2f Chunk::GlobalToChunkIndexPosition(int x, int y){
    Vector2f v(x, y);
    v.x = floor(v.x / ChunkSize);
    v.y = floor(v.y / ChunkSize);
    return  v;
}
