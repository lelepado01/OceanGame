//
//  TextureAtlas.cpp
//  OceanGame
//
//  Created by Gabriele Padovani on 26/12/21.
//

#include "TextureAtlas.hpp"

TextureAtlas::TextureAtlas(const std::string& path){
    texture = Engine::LoadTexture(path);
}

TextureAtlas::~TextureAtlas(){
    Engine::DeleteTexture(texture);
}

SDL_Texture* TextureAtlas::GetTexture(){
    return texture;
}

void TextureAtlas::AddTileDescriptor(int tile, SDL_Rect bounds){
    tileDescriptors[tile] = bounds;
}

SDL_Rect TextureAtlas::GetTileDescriptor(int tile){
    return tileDescriptors[tile];
}


