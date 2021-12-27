//
//  UiTextWithValue.cpp
//  EngineTemplate
//
//  Created by Gabriele Padovani on 25/12/21.
//

#include "UiTextWithValue.hpp"

UiTextWithValue::UiTextWithValue(const std::string& label, float* v){
    this->label = label;
    this->value = v;
    
    this->w = 400;
    this->h = 50;
    
    labelTexture = Engine::LoadTextureFromText(label);
}

UiTextWithValue::~UiTextWithValue(){
    Engine::DeleteTexture(labelTexture);
}

void UiTextWithValue::Update(int offsetX, int offsetY) {
    std::string completeLabel = label.c_str() + std::string(" ") + std::to_string(*value);
    this->w = textLetterSize * (int)completeLabel.length();
    
    Engine::DeleteTexture(labelTexture);
    labelTexture = Engine::LoadTextureFromText(completeLabel);
}

void UiTextWithValue::Draw(int offsetX, int offsetY){
    Engine::RenderTexture(labelTexture, offsetX, offsetY, w, h);
}
