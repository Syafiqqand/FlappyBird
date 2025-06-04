#pragma once
#include <raylib.h>

class Pipe {
public:
    Rectangle upper;
    Rectangle lower;
    bool passed = false;
    
    Pipe(float x, float gapY);
    void Update();
    void Draw() const;
    bool IsOffScreen() const;
};