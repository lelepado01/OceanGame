
#include <stdio.h>
#include <iostream>

#include "Gui.hpp"
#include "Engine.hpp"
#include "Time.hpp"
#include "game/tilemap/Tilemap.hpp"

int main(int, char**) {
    
    Engine::InitSDL();
    SDL_Color clearColor = {255,255,255,255};
    
    Tilemap tilemap;

    float fps = 0;
    
    while (Engine::IsRunning()) {
        Time::Count();
        
        Gui::NewFrame();
        
        Engine::HandleEvents();
        Engine::ClearScreen(clearColor);
        
        tilemap.Update();
        tilemap.Draw(); 
        
        Gui::Begin("Window 1", 100,600, true, true);

        fps = (int)Time::FPS();
        Gui::CreateTextWithValue("FPS: ", &fps);
        
        Gui::End();


        Gui::Update();
        Gui::Draw();

        Engine::Render();
    }
    
    Engine::CleanupSDL();
    
    return 0;
}
