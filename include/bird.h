#pragma once
#include <raylib.h>

class Pipe; // Forward declaration

class Bird {
    float x, y;
    float velocity;
    
    // Variabel animasi baru
    Texture2D texture;
    Rectangle frameRec;
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    
public:
    Bird();
    void SetTexture(Texture2D tex);
    void Update();
    void Draw() const;
    Rectangle GetRect() const;
    void Jump();
    bool CheckCollision(const Pipe& pipe) const;

    static constexpr float gravity = 0.5f;
    static constexpr float jumpForce = -8.0f;
};