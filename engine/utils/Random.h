//
//  Random.h
//  EngineTemplate
//
//  Created by Gabriele Padovani on 28/09/21.
//

#ifndef Random_h
#define Random_h

#include <ctime>

class Random {
private:
    
public:
    static int RandRange(int r){
        srand(floor(time(NULL)));
        return rand() % r;
    }
    
    static int RandPerlin(int x, int y); 
};

#endif /* Random_h */
