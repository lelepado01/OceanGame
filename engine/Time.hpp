//
//  Time.hpp
//  SdlTest2
//
//  Created by Gabriele Padovani on 28/08/21.
//

#ifndef Time_hpp
#define Time_hpp

#include <stdio.h>
#include <iostream>
#include <chrono>

class Time {
private:
    static float deltaTime;

    static std::chrono::time_point<std::chrono::steady_clock> old_time;
    static std::chrono::time_point<std::chrono::steady_clock> new_time;

public:
    static float FPS();
    static float DeltaTime();
    static void Count();
};

#endif /* Time_hpp */
