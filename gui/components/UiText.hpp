//
//  UiText.hpp
//  EngineTemplate
//
//  Created by Gabriele Padovani on 21/12/21.
//

#ifndef UiText_hpp
#define UiText_hpp

#include <stdio.h>
#include <string>

#include "UiComponent.hpp"
#include "../../engine/Engine.hpp"

class UiText : public UiComponent {
protected: 
    
public:
    UiText(const std::string& label);
    ~UiText();
    
    void Update(int offsetX, int offsetY) override {};
    void Draw(int offsetX, int offsetY) override;

    inline ComponentType GetType() override { return ComponentType::TextType; };
};

#endif /* UiText_hpp */
