//
//  UiTextWithValue.hpp
//  EngineTemplate
//
//  Created by Gabriele Padovani on 25/12/21.
//

#ifndef UiTextWithValue_hpp
#define UiTextWithValue_hpp

#include <stdio.h>
#include <string>

#include "UiComponent.hpp"
#include "../../engine/Engine.hpp"

class UiTextWithValue : public UiComponent {
protected:
    float* value;
    
public:
    UiTextWithValue(const std::string& label, float* v);
    ~UiTextWithValue();
    
    void Update(int offsetX, int offsetY) override;
    void Draw(int offsetX, int offsetY) override;

    inline ComponentType GetType() override { return ComponentType::TextWithValueType; };
};

#endif /* UiTextWithValue_hpp */
