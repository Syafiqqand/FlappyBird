#pragma once
#include <raylib.h>

class Pipe; 

class Bird {
    float x, y;
    float velocity;
    
    Texture2D texture;
    Rectangle frameRec;
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    
    float gravity;
    float jumpForce;
    
public:
    Bird();
    void SetTexture(Texture2D tex); 
    void Update();
    void Draw() const;
    Rectangle GetRect() const;
    void Jump();
    bool CheckCollision(const Pipe& pipe) const;
};