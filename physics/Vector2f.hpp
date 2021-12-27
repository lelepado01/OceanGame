//
//  Vector2f.hpp
//  ShooterSDL
//
//  Created by Gabriele Padovani on 30/08/21.
//

#ifndef Vector2f_hpp
#define Vector2f_hpp

#include <stdio.h>
#include <math.h>

class Vector2f {
public:
    float x, y;
    
    Vector2f();
    Vector2f(const float x, const float y);
    
    static Vector2f Random(const int r);
    
    void Add(const Vector2f& v);
    void Sub(const Vector2f& v);
    void Mult(const Vector2f& v);
    void Mult(const float f);
    void Div(const Vector2f& v);
    void Div(const float f);
    
    static float Cross(const Vector2f& v1, const Vector2f& v2);
    static float Distance(const Vector2f& v1, const Vector2f& v2);
    
    void Normalize();
    void Rotate(const unsigned int angle);
    int GetAngle() const;
    
    bool operator !=(const Vector2f& v);
    bool operator ==(const Vector2f& v);
};

#endif /* Vector2f_hpp */
