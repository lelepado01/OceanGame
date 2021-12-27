//
//  Engine.hpp
//  SdlTest2
//
//  Created by Gabriele Padovani on 28/08/21.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>

class Engine {
private:
    static SDL_Renderer* Renderer;
    static SDL_Window* Window;
    static bool running;
    
    static bool debugMode;

    static TTF_Font* font; 
    
    static const int maxKeys = 100;
    static int KEYS[maxKeys];
    static SDL_Point mousePosition;
    static bool mouseLeftPressed;
    static bool mouseRightPressed;
    
    static SDL_Color engineDrawColor; 
    
public:
    static const int WINDOW_WIDTH = 1280;
    static const int WINDOW_HEIGHT = 720;

    static void LogSDLError(std::ostream &os, const std::string &msg);
    static void InitSDL();
    static void CleanupSDL();
    
    static void ClearScreen(SDL_Color color);
    static void Render();
    static void HandleEvents();
    static bool KeyIsPressed(SDL_Keycode key);
    
    inline static bool MouseLeftKeyIsPressed() { return mouseLeftPressed; };
    inline static bool MouseRightKeyIsPressed() { return mouseRightPressed; };
    inline static SDL_Point GetMousePosition() { return SDL_Point{ mousePosition.x * 2, mousePosition.y * 2}; };
    
    inline static bool IsRunning() { return running; };  
    
    static SDL_Texture* LoadTexture(const std::string &file);
    static SDL_Texture* LoadTextureFromText(const std::string& text);
    
    static void RenderTexture(SDL_Texture *tex, int x, int y, int w, int h);
    static void RenderTexture(SDL_Texture *tex, int x, int y, int w, int h, double angle);
    static void RenderTexture(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst);
    
    static void SetTextureColor(SDL_Texture *tex, int r, int g, int b); 
    
    static void DeleteTexture(SDL_Texture *tex);
    
    static void SetEngineDrawColor(int r, int g, int b, int a);
    static void SetEngineScale(int scale);
    
    static void DrawLine(int x1, int y1, int x2, int y2);
    
    static void DrawRectangle(int x, int y, int w, int h);
    static void FillRectangle(int x, int y, int w, int h);
    
    static void DrawPolygon(const std::vector<SDL_Point>& points);
    static void FillPolygon(const std::vector<SDL_Point>& points);
    
    static void DrawPixel(float x, float y);
    static void DrawPixels(SDL_Point* array, int length);
};


#endif /* Engine_hpp */
