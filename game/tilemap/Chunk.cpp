//
//  Chunk.cpp
//  OceanGame
//
//  Created by Gabriele Padovani on 27/12/21.
//

#include "Chunk.hpp"

Chunk::Chunk(int x, int y){
    offsetX = x;
    offsetY = y;
    
    for (int x = 0; x < TileNumber; x++) {
        for (int y = 0; y < TileNumber; y++) {
            tiles[x][y] = Tile{(TileName)(rand() % 3), 10};
        }
    }
}

Chunk::~Chunk(){
    
}

TileName Chunk::getTileType(int x, int y){
    if (x < 0 || x > TileNumber || y < 0 || y > TileNumber){
        return TileName::GROUND;
    }
        
    return tiles[x][y].name;
}


void Chunk::Draw(const TextureAtlas& textureAtlas, const Vector2f& mapOffset){
    for (int x = 0; x < TileNumberX; x++) {
        for (int y = 0; y < TileNumberY; y++) {
            
            SDL_Rect tileBounds = textureAtlas.GetTileDescriptor(getTileType(x, y));
            SDL_Rect tilePos = SDL_Rect{x * TileSize - (int)mapOffset.x, y * TileSize - (int)mapOffset.y, TileSize, TileSize};
            
            Engine::SetTextureColor(textureAtlas.GetTexture(),
                                    255-255*y / TileNumberY,
                                    255-255*y / TileNumberY,
                                    255-255*y / TileNumberY);
            
            Engine::RenderTexture(textureAtlas.GetTexture(), tileBounds, tilePos);
        }
    }
}

SDL_Point Chunk::ToChunkPosition(SDL_Point &point){
    return SDL_Point{point.x / TileSize, point.y / TileSize}; 
}

bool Chunk::pointInWindow(int x, int y){
    return offsetX > x && offsetX < x + Engine::WINDOW_WIDTH*2 && offsetY > y && offsetY < y + Engine::WINDOW_HEIGHT*2;
}

bool Chunk::InWindow(int windowStartX, int windowStartY){
    return pointInWindow(windowStartX, windowStartY)
        || pointInWindow(windowStartX + TileNumber * TileSize, windowStartY)
        || pointInWindow(windowStartX, windowStartY + TileNumber * TileSize)
        || pointInWindow(windowStartX + TileNumber * TileSize, windowStartY + TileNumber * TileSize);

}
