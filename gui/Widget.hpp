//
//  Widget.hpp
//  EngineTemplate
//
//  Created by Gabriele Padovani on 30/10/21.
//

#ifndef Widget_hpp
#define Widget_hpp

#include <stdio.h>
#include <optional>

#include "UiComponent.hpp"


struct Widget {
    const static int WidgetPadding = 20;
    const static int WidgetBorder = 2;
    const static int ResizeTriangleSize = 20;
    const static int TopBarHeight = 50;
        
    constexpr static SDL_Color WindowColor = SDL_Color{0, 160, 145, 255};
    constexpr static SDL_Color TopBarColor = SDL_Color{50, 50, 50, 255};

    bool moveable;
    bool resizeable; 
    
    int x, y, w, h;
    int minWidth, minHeight;
    int componentIndex = 0;
    
    SDL_Texture* labelTexture; 
    
    std::vector<UiComponent*> components = std::vector<UiComponent*>(10);
    
    std::optional<SDL_Point> mouseMoveGrab = {};
    std::optional<SDL_Point> mouseResizeGrab = {};

    bool isBeingMoved(){ return mouseMoveGrab.has_value(); };
    bool isBeingResized(){ return mouseResizeGrab.has_value(); };
    bool isBeingInteractedWith(){
        for (int i = 0; i < componentIndex; i++) {
            if (components[i]->GetType() == ComponentType::SliderType){
                if (((Slider*)components[i])->SliderIsBeingGrabbed()) return true;
            }
        }
        return false;
    };
    
    void addComponent(UiComponent* component){
        components[componentIndex] = component;
        
        w = std::max(w, component->GetWidth());
        h += component->GetHeight();
        
        minWidth = w;
        minHeight = h;
        
        componentIndex += 1;
    }
    
    void Draw(){
        drawTopBar();
        drawWindow();
        drawComponents();
    }
    
    void drawWindow(){
        Engine::SetEngineDrawColor(WindowColor.r, WindowColor.g, WindowColor.b, WindowColor.a);
        Engine::FillRectangle(x, y + TopBarHeight, w, h);
            
        if (resizeable){
            drawResizeTriangle();
        }
    }
    
    void drawTopBar(){
        Engine::SetEngineDrawColor(TopBarColor.r, TopBarColor.g, TopBarColor.b, TopBarColor.a);
        Engine::FillRectangle(x - WidgetBorder, y, w + WidgetBorder * 2, TopBarHeight + h + WidgetBorder);
        Engine::RenderTexture(labelTexture, x + WidgetPadding, y, TopBarHeight * 3, TopBarHeight);
    }
    
    void drawResizeTriangle(){
        std::vector<SDL_Point> points = {
            SDL_Point{x + w, y + TopBarHeight + h - Widget::ResizeTriangleSize},
            SDL_Point{x + w, y + TopBarHeight + h},
            SDL_Point{x + w - Widget::ResizeTriangleSize, y + TopBarHeight + h}
        };
        
        Engine::SetEngineDrawColor(TopBarColor.r, TopBarColor.g, TopBarColor.b, TopBarColor.a);
        Engine::FillPolygon(points);

    }
    
    void drawComponents(){
        int componentsOffsetY = 0;
        for (int j = 0; j < componentIndex; j++) {
            int offsetX = x + Widget::WidgetPadding;
            int offsetY = y + Widget::WidgetPadding + TopBarHeight + componentsOffsetY;
            
            components[j]->Draw(offsetX, offsetY);
            
            componentsOffsetY += components[j]->GetHeight() + Widget::WidgetPadding;
        }
    }
};

#endif /* Widget_hpp */
