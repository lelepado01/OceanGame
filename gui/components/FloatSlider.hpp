//
//  FloatSlider.hpp
//  EngineTemplate
//
//  Created by Gabriele Padovani on 30/10/21.
//

#ifndef FloatSlider_hpp
#define FloatSlider_hpp

#include <stdio.h>

#include "Engine.hpp"
#include "Slider.hpp"
#include "UiComponent.hpp"

class FloatSlider : public Slider {
private:
    float* content;
    
    inline float getPercentageInRange() { return ((float)*(content) - min) / (max - min); };
    inline float getValueOfSliderFromPercentage(float perc) { return perc * (max - min) + min; };

    std::string getValueAsFormattedString();

    bool updateSliderValue(int newX, int offsetX);
    
public:
    FloatSlider(const std::string& label, float* c, float min, float max);
    ~FloatSlider();
    
    void Update(int offsetX, int offsetY) override;
    void Draw(int offsetX, int offsetY) override;
};


#endif /* FloatSlider_hpp */
