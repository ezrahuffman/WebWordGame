//
// A small library for timing our programs
//

#ifndef TimeSupport_h
#define TimeSupport_h

#include <chrono>

typedef enum {
    sec,
    mill
} Unit;

typedef std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;

long time_diff(timestamp start, timestamp end, Unit u = mill){
    
    if (u == mill){
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        
        return (long) diff;
    }
    else{
        auto diff = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
        
        return (long) diff;
    }
}


timestamp current_time(){
    return std::chrono::high_resolution_clock::now();
}

#endif

