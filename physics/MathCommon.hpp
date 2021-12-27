//
//  math_common.hpp
//  EngineTemplate
//
//  Created by Gabriele Padovani on 31/10/21.
//

#ifndef math_common_hpp
#define math_common_hpp

#include <SDL.h>

class MathCommon {    
public:
    static bool RectangleContainsPoint(const SDL_Rect& rect, const SDL_Point& point){
        return point.x < rect.x + rect.w && point.x > rect.x && point.y < rect.y + rect.h && point.y > rect.y;
    }
};

#endif /* math_common_hpp */
