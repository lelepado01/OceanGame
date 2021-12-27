//
//  IntSlider.cpp
//  EngineTemplate
//
//  Created by Gabriele Padovani on 30/10/21.
//

#include "IntSlider.hpp"

IntSlider::IntSlider(const std::string& label, int* v, int min, int max){
    this->label = label; 
    this->content = v;
    this->min = min;
    this->max = max;
    
    this->w = 300;
    this->h = 80;
    
    this->labelTexture = Engine::LoadTextureFromText(label.c_str());
    this->valueTexture = Engine::LoadTextureFromText(getValueAsFormattedString().c_str());
}

IntSlider::~IntSlider(){
    Engine::DeleteTexture(labelTexture);
    Engine::DeleteTexture(valueTexture);
    delete &label;
}

void IntSlider::Draw(int offsetX, int offsetY){
    int labelWidth = textLetterSize * (int)label.length();
    Engine::RenderTexture(labelTexture, offsetX, offsetY, labelWidth, h);
    Engine::RenderTexture(valueTexture,
                          offsetX + w + textPadding,
                          offsetY,
                          textLetterSize * (int)getValueAsFormattedString().length(),
                          h);
    
    Engine::SetEngineDrawColor(50, 50, 50, 255);
    Engine::FillRectangle(offsetX, offsetY + h + sliderPadding, w + sliderHandleWidth, h / 2);
    
    int xstart = offsetX + w * getPercentageInRange();
    Engine::SetEngineDrawColor(255, 255, 255, 255);
    Engine::FillRectangle(xstart, offsetY + h + sliderPadding, sliderHandleWidth, h / 2);
}

void IntSlider::Update(int offsetX, int offsetY){
    if (Engine::MouseLeftKeyIsPressed()){
        SDL_Point mouse = Engine::GetMousePosition();
        
        int sliderHandleXstart = offsetX + w * getPercentageInRange();
        int sliderHandleYstart = offsetY + h + sliderPadding;
        
        SDL_Rect sliderHandleArea {sliderHandleXstart, sliderHandleYstart, sliderHandleWidth, h / 2};
        
        if (MathCommon::RectangleContainsPoint(sliderHandleArea, mouse) || SliderIsBeingGrabbed()) {
            
            if (SliderIsBeingGrabbed()){
                
                bool updated = updateSliderValue(mouse.x, offsetX);
                if (updated){
                    Engine::DeleteTexture(valueTexture);
                    valueTexture = Engine::LoadTextureFromText(getValueAsFormattedString().c_str());
                }
            }
            
            sliderMouseGrab = mouse.x - sliderHandleXstart;
        }
    } else {
        sliderMouseGrab = {};
    }
}

bool IntSlider::updateSliderValue(int newX, int offsetX){
    int oldContent = *content;
    
    float newPercSlider = float(newX - offsetX) / w;
    *content = getValueOfSliderFromPercentage(newPercSlider);
    
    if (*content < min) *content = min;
    if (*content > max) *content = max;
    
    return oldContent != *content;
}
