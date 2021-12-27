//
//  IntSlider.hpp
//  EngineTemplate
//
//  Created by Gabriele Padovani on 30/10/21.
//

#ifndef IntSlider_hpp
#define IntSlider_hpp

#include <stdio.h>
#include <optional>

#include "Engine.hpp"
#include "UiComponent.hpp"
#include "Slider.hpp"

class IntSlider : public Slider {
private:
    int* content;
    
    inline float getPercentageInRange() { return ((float)*(content) - min) / (max - min); };
    inline int getValueOfSliderFromPercentage(float perc) { return (int)floor(perc * (max - min)) + min; };
    inline std::string getValueAsFormattedString(){ return std::to_string(*content); };

    bool updateSliderValue(int newX, int offsetX);
            
public:
    IntSlider(const std::string& label, int* c, int min, int max);
    ~IntSlider();
    
    void Update(int offsetX, int offsetY) override;
    void Draw(int offsetX, int offsetY) override;    
};


#endif /* IntSlider_hpp */
