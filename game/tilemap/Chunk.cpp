//
//  Chunk.cpp
//  OceanGame
//
//  Created by Gabriele Padovani on 27/12/21.
//

#include "Chunk.hpp"

Chunk::Chunk(const int x, const int y){
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

TileName Chunk::getTileType(const int x, const int y) const {
    if (x < 0 || x >= TileNumber || y < 0 || y >= TileNumber){
        return TileName::GROUND;
    }
        
    return tiles[x][y].name;
}


Vector2f Chunk::getStartOfVisibleChunk(const Vector2f& mapOffset) const {
    Vector2f drawStart(fmax(chunkRectangle.x, mapOffset.x),
                       fmax(chunkRectangle.y, mapOffset.y));
    drawStart = RelativeToTileCoordinate(GlobalToRelativeChunkPosition(drawStart));
    
    if ( drawStart.y > 0) drawStart.y -= 1;
    
    return drawStart;
}


Vector2f Chunk::getEndOfVisibleChunk(const Vector2f& mapOffset) const {
    Vector2f endOfWindow(mapOffset.x + Engine::GetWindowWidth(),
                         mapOffset.y + Engine::GetWindowHeight());
    
    Vector2f drawEnd(fmin(chunkRectangle.x + ChunkSize, endOfWindow.x),
                     fmin(chunkRectangle.y + ChunkSize, endOfWindow.y));
    return RelativeToTileCoordinate(GlobalToRelativeChunkPosition(drawEnd));
}

void Chunk::Draw(const TextureAtlas& textureAtlas, const Vector2f& mapOffset){
  
    Vector2f drawStart = getStartOfVisibleChunk(mapOffset);
    Vector2f drawEnd = getEndOfVisibleChunk(mapOffset);
    
    for (int y = drawStart.y; y < drawEnd.y; y++) {
        for (int x = drawStart.x; x < drawEnd.x; x++) {
            
            Vector2f relativePos = TileToGlobalCoordinate(Vector2f(x, y));
            relativePos.Sub(mapOffset);
            
            SDL_Rect tileBounds = textureAtlas.GetTileDescriptor(getTileType(x, y));
            SDL_Rect tilePos = SDL_Rect{(int)relativePos.x, (int)relativePos.y, TileSize, TileSize};
            
            Engine::RenderTexture(textureAtlas.GetTexture(), tileBounds, tilePos);
        }
        
        Engine::SetTextureColor(textureAtlas.GetTexture(),
                                255-255*y / TileNumber,
                                255-255*y / TileNumber,
                                255-255*y / TileNumber);
    }
}

Vector2f Chunk::GetChunkPosition() const {
    return Vector2f(chunkPositionX, chunkPositionY);
}

bool Chunk::InWindow(const int windowStartX, const int windowStartY) const {
    SDL_Rect window {windowStartX, windowStartY, Engine::GetWindowWidth(), Engine::GetWindowHeight()};
    SDL_Rect res;
    return SDL_IntersectRect(&window, &chunkRectangle, &res) == SDL_TRUE;
}

Vector2f Chunk::GlobalToRelativeChunkPosition(const Vector2f& v) const {
    return Vector2f(v.x - chunkRectangle.x, v.y - chunkRectangle.y);
}

Vector2f Chunk::RelativeToTileCoordinate(const Vector2f& v) const {
    return Vector2f(v.x / TileSize, v.y / TileSize);
}

Vector2f Chunk::TileToGlobalCoordinate(const Vector2f &v) const {
    return Vector2f(v.x * TileSize + chunkRectangle.x, v.y * TileSize + chunkRectangle.y);
}

Vector2f Chunk::GlobalToChunkIndexPosition(const int x, const int y) {
    Vector2f v(x, y);
    v.x = floor(v.x / ChunkSize);
    v.y = floor(v.y / ChunkSize);
    return  v;
}
