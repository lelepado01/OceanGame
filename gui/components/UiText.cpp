//
//  Text.cpp
//  EngineTemplate
//
//  Created by Gabriele Padovani on 21/12/21.
//

#include "UiText.hpp"

UiText::UiText(const std::string& label){
    this->label = label;

    this->w = 400;
    this->h = 50;
    
    this->labelTexture = Engine::LoadTextureFromText(label.c_str());
}

UiText::~UiText(){
    Engine::DeleteTexture(labelTexture);
}

void UiText::Draw(int offsetX, int offsetY){
    int labelWidth = textLetterSize * (int)label.length();
    Engine::RenderTexture(labelTexture, offsetX, offsetY, labelWidth, h);
}
