//
//  Time.cpp
//  SdlTest2
//
//  Created by Gabriele Padovani on 28/08/21.
//

#include "Time.hpp"

float Time::deltaTime = 0;
std::chrono::time_point<std::chrono::steady_clock> Time::old_time = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> Time::new_time = std::chrono::steady_clock::now();

float Time::DeltaTime(){
    return deltaTime <= 0 || deltaTime > 10000 ?  0.001 : deltaTime;
}

float Time::FPS(){
    return 1 / deltaTime;
}

void Time::Count(){
    old_time = new_time;
    new_time = std::chrono::steady_clock::now();
    
    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(new_time - old_time).count() / 1000.0f;
}
