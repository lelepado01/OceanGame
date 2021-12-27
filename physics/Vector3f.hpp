//
//  Vector3f.hpp
//  IsometricEngine
//
//  Created by Gabriele Padovani on 08/10/21.
//

#ifndef Vector3f_hpp
#define Vector3f_hpp

#include <stdio.h>
#include <math.h>


class Vector3f {
public:
    float x, y, z;
    
    Vector3f();
    Vector3f(const float x, const float y, const float z);
    
    static Vector3f Random(const int r);
    
    void Add(const Vector3f& v);
    void Sub(const Vector3f& v);
    void Mult(const Vector3f& v);
    void Mult(const float f);
    void Div(const Vector3f& v);
    void Div(const float f);
    
    static float Cross(const Vector3f& v1, const Vector3f& v2);
    static float Distance(const Vector3f& v1, const Vector3f& v2);
    
    void Normalize();
    void Rotate(const unsigned int angle);
    int GetAngle() const;
    
    bool operator !=(const Vector3f& v);
    bool operator ==(const Vector3f& v);
};



#endif /* Vector3f_hpp */
