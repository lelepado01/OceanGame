//
//  FloatSlider.cpp
//  EngineTemplate
//
//  Created by Gabriele Padovani on 30/10/21.
//

#include "FloatSlider.hpp"

FloatSlider::FloatSlider(const std::string& label, float* v, float min, float max){
    this->label = label; 
    this->content = v;
    this->min = min; 
    this->max = max;
    
    this->w = 400;
    this->h = 80;
    
    this->labelTexture = Engine::LoadTextureFromText(label.c_str());
    this->valueTexture = Engine::LoadTextureFromText(getValueAsFormattedString().c_str());
}

FloatSlider::~FloatSlider(){
    Engine::DeleteTexture(labelTexture);
    Engine::DeleteTexture(valueTexture);
}

std::string FloatSlider::getValueAsFormattedString(){
    std::string ret = std::to_string(*content);
    
    int indexOfDot = 0;
    for (int i=0; i < ret.length(); i++) {
        if (ret[i] == '.'){
            indexOfDot = i;
            break;
        }
    }

    return ret.substr(0, indexOfDot+3);
}

void FloatSlider::Draw(int offsetX, int offsetY){
    
    int labelWidth = textLetterSize * (int)label.length();
    Engine::RenderTexture(labelTexture, offsetX, offsetY, labelWidth, sliderHeight);
    Engine::RenderTexture(valueTexture,
                          offsetX + w + textPadding,
                          offsetY,
                          textLetterSize * (int)getValueAsFormattedString().length(),
                          sliderHeight);
    
    Engine::SetEngineDrawColor(50, 50, 50, 255);
    Engine::FillRectangle(offsetX, offsetY + sliderHeight + sliderPadding, w + sliderHandleWidth, sliderHeight / 2);
    
    int xstart = offsetX + w * getPercentageInRange();
    Engine::SetEngineDrawColor(255, 255, 255, 255);
    Engine::FillRectangle(xstart, offsetY + sliderHeight + sliderPadding, sliderHandleWidth, sliderHeight / 2);
}

void FloatSlider::Update(int offsetX, int offsetY){
    if (Engine::MouseLeftKeyIsPressed()){
        SDL_Point mouse = Engine::GetMousePosition();
        
        int sliderHandleXstart = offsetX + w * getPercentageInRange();
        int sliderHandleYstart = offsetY + sliderHeight + sliderPadding;
        
        SDL_Rect sliderHandleArea {sliderHandleXstart, sliderHandleYstart, sliderHandleWidth, sliderHeight / 2};
        
        if (MathCommon::RectangleContainsPoint(sliderHandleArea, mouse) || SliderIsBeingGrabbed()) {
            
            if (SliderIsBeingGrabbed()){
                
                bool updated = updateSliderValue(mouse.x, offsetX);
                if (updated){
                    SDL_Texture* oldValueTexture = valueTexture;
                    valueTexture = Engine::LoadTextureFromText(getValueAsFormattedString().c_str());
                    Engine::DeleteTexture(oldValueTexture);
                }
            }
            
            sliderMouseGrab = mouse.x - sliderHandleXstart;
        }
    } else {
        sliderMouseGrab = {};
    }
}

bool FloatSlider::updateSliderValue(int newX, int offsetX){
    float oldContent = *content;
    
    float newPercSlider = float(newX - offsetX) / w;
    *content = getValueOfSliderFromPercentage(newPercSlider);
    
    if (*content < min) *content = min;
    if (*content > max) *content = max;
    
    return oldContent != *content;
}
