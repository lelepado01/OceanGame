//
//  Gui.hpp
//  EngineTemplate
//
//  Created by Gabriele Padovani on 29/10/21.
//

#ifndef Gui_hpp
#define Gui_hpp

#include <stdio.h>
#include <math.h>

#include "Engine.hpp"
#include "FloatSlider.hpp"
#include "IntSlider.hpp"
#include "Checkbox.hpp"
#include "Widget.hpp"
#include "UiText.hpp"
#include "UiTextWithValue.hpp"
#include "MathCommon.hpp"

class Gui {
private:
    static const int initialWidgetHeight = 100;

    static int widgetIndex;
    static int lastFrameWidgetsCount;
    
    static bool widgetIsBeingMoved;
    static bool widgetIsBeingResized;
    static bool widgetSliderIsBeingDragged;

    static std::vector<Widget> widgets;
    static Widget tempWidget;
    
    static bool checkWidgetForMouseDrag(Widget& widget);
    static bool checkWidgetForMouseResize(Widget& widget);
    static bool checkWidgetForSliderGrab(Widget& widget);
    
    static void updateWidgetComponents(Widget& widget);

    static void handleWidgetsResize();
    static void handleWidgetsMove();
    static void handleWidgetsSliders(); 
        
    static bool widgetIsNew();
    
public:
    static void NewFrame(); 
    static void Begin(const std::string& label, int x, int y, bool moveable=false, bool resizeable=false);
    static void End();
    
    static void Update();
    static void Draw();
    
    static void CreateText(const std::string& label);
    static void CreateCheckbox(const std::string& label, bool* v);
    static void CreateFloatSlider(const std::string& label, float* v, float min, float max);
    static void CreateIntSlider(const std::string& label, int* v, int min, int max);
    static void CreateTextWithValue(const std::string& label, float* v);

};


#endif /* Gui_hpp */
