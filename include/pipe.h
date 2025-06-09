#pragma once
#include <raylib.h>

class Pipe {
public:
    // Collider bagian atas dan bawah
    Rectangle upper;
    Rectangle lower;
    bool passed = false;

    // --- Variabel animasi ---
    Texture2D texture;      
    Rectangle frameRec;     
    int     currentFrame;   
    int     framesCounter;  
    int     framesSpeed;    
    int     maxFrames;      
    int     cols, rows;     
    float   frameWidth;     
    float   frameHeight;    

    // --- Scaling & ukuran gap ---
    float   desiredWidth;   
    float   scale;          
    float   gapHeight;      

    Pipe(float x, float gapY, float _gapHeight, Texture2D tex, float _desiredWidth);

    void Update();
    void Draw() const;
    bool IsOffScreen() const;
};
