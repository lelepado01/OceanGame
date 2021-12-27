//
//  Engine.cpp
//  SdlTest2
//
//  Created by Gabriele Padovani on 28/08/21.
//

#include "Engine.hpp"

bool Engine::running = true;
bool Engine::debugMode = false;
SDL_Window* Engine::Window = nullptr;
SDL_Renderer* Engine::Renderer = nullptr;
TTF_Font* Engine::font = nullptr;

int Engine::KEYS[100];
SDL_Point Engine::mousePosition = SDL_Point();
bool Engine::mouseLeftPressed = false;
bool Engine::mouseRightPressed = false;

SDL_Color Engine::engineDrawColor = SDL_Color{0,0,0,0};

void Engine::LogSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}


void Engine::InitSDL(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        LogSDLError(std::cout, "SDL_Init Error");
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetSwapInterval(1); // Enable vsync
    
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    Window = SDL_CreateWindow("Sdl2 Test",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              window_flags);
    
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer == nullptr) {
        SDL_DestroyWindow(Window);
        LogSDLError(std::cout, "SDL_CreateRenderer Error");
        SDL_Quit();
    }
    
    TTF_Init();
    font = TTF_OpenFont("/Users/gabrielepadovani/Desktop/Code/C++/EngineTemplate/EngineTemplate/assets/font.ttf", 80);
    
    for(int i = 0; i < 322; i++) {
       KEYS[i] = false;
    }
}

void Engine::CleanupSDL(){
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
}



SDL_Texture* Engine::LoadTexture(const std::string& file){
    SDL_Texture *texture = IMG_LoadTexture(Renderer, file.c_str());
    if (texture == nullptr){
        LogSDLError(std::cout, "LoadTexture");
    }
    return texture;
}

SDL_Texture* Engine::LoadTextureFromText(const std::string& text) {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Renderer, surface);
    
    SDL_FreeSurface(surface);
    if (tex == nullptr){
        LogSDLError(std::cout, "LoadTextureFromText");
    }
    
    return tex;
}


void Engine::RenderTexture(SDL_Texture *tex, int x, int y, int w, int h){
    SDL_Rect dst = {x , y, w, h};
    SDL_RenderCopy(Renderer, tex, NULL, &dst);
}

void Engine::RenderTexture(SDL_Texture *tex, int x, int y, int w, int h, double angle){
    SDL_Rect dst = {x , y, w, h};
    SDL_RenderCopyEx(Renderer, tex, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
}

void Engine::RenderTexture(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst){
    SDL_RenderCopy(Renderer, tex, &src, &dst);
}

void Engine::SetTextureColor(SDL_Texture *tex, int r, int g, int b){
    SDL_SetTextureColorMod(tex, r, g, b); 
}

void Engine::ClearScreen(SDL_Color color) {
    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(Renderer);
}

void Engine::Render() {
    SDL_RenderPresent(Renderer);
}

void Engine::HandleEvents(){
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        SDL_GetMouseState( &mousePosition.x, &mousePosition.y );
        
        if (event.type == SDL_QUIT)
            running = false;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(Window))
            running = false;
        if (event.type == SDL_KEYDOWN){
            for (int i = 0; i < maxKeys; i++) {
                if (KEYS[i] == 0 || KEYS[i] == event.key.keysym.sym){
                    KEYS[i] = event.key.keysym.sym;
                    
                    break;
                }
            }
        }
        if (event.type == SDL_KEYUP){
            for (int i = 0; i < maxKeys; i++) {
                if (KEYS[i] == event.key.keysym.sym){
                    KEYS[i] = 0;
                }
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN){
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseLeftPressed = true;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                mouseRightPressed = true;
            }
        }
        if (event.type == SDL_MOUSEBUTTONUP){
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseLeftPressed = false;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                mouseRightPressed = false;
            }
        }
    }
}

bool Engine::KeyIsPressed(SDL_Keycode key){
    for (int i = 0; i < maxKeys; i++) {
        if (KEYS[i] == key){
            return true;
        }
    }
    return false;
}

void Engine::DeleteTexture(SDL_Texture *tex){
    SDL_DestroyTexture(tex); 
}


void Engine::DrawLine(int x1, int y1, int x2, int y2){
    SDL_RenderDrawLine(Renderer, x1, y1, x2, y2);
}

void Engine::DrawRectangle(int x, int y, int w, int h){
    SDL_Rect r = SDL_Rect{x, y, w, h};
    SDL_RenderDrawRect(Renderer, &r);
}

void Engine::FillRectangle(int x, int y, int w, int h){
    SDL_Rect r = SDL_Rect{x, y, w, h};
    SDL_RenderFillRect(Renderer, &r);
}

void Engine::DrawPixels(SDL_Point *array, int length){
    SDL_RenderDrawPoints(Renderer, array, length);
}

void Engine::SetEngineDrawColor(int r, int g, int b, int a){
    engineDrawColor = SDL_Color{(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
    SDL_SetRenderDrawColor(Renderer, r, g, b, a);
}

void Engine::SetEngineScale(int scale){
    SDL_RenderSetScale(Renderer, scale, scale);
}

void Engine::DrawPixel(float x, float y){
    SDL_RenderDrawPoint(Renderer, x, y);
}

void Engine::DrawPolygon(const std::vector<SDL_Point> &points){
    
}

void Engine::FillPolygon(const std::vector<SDL_Point> &points){
    short xPoints[points.size()];
    short yPoints[points.size()];
    
    for (int i =0; i < points.size(); i++) {
        xPoints[i] = points[i].x;
        yPoints[i] = points[i].y;
    }
    
    filledPolygonRGBA(Renderer,
                      xPoints,
                      yPoints,
                      (int)points.size(),
                      engineDrawColor.r,
                      engineDrawColor.g,
                      engineDrawColor.b,
                      engineDrawColor.a);
}
