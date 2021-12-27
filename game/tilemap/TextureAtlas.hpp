//
//  TextureAtlas.hpp
//  OceanGame
//
//  Created by Gabriele Padovani on 26/12/21.
//

#ifndef TextureAtlas_hpp
#define TextureAtlas_hpp

#include <stdio.h>
#include <SDL.h>
#include <string>
#include <unordered_map>

#include "../../engine/Engine.hpp"


class TextureAtlas {
private:
    std::string path;
    std::unordered_map<int, SDL_Rect> tileDescriptors = std::unordered_map<int, SDL_Rect>();
    
    SDL_Texture* texture;
    
public:
    TextureAtlas(const std::string& path);
    ~TextureAtlas();
    
    void AddTileDescriptor(int tile, SDL_Rect bounds);
    SDL_Rect GetTileDescriptor(int tile) const;
    
    SDL_Texture* GetTexture() const;
};

#endif /* TextureAtlas_hpp */
