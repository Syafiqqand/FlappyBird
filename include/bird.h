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
    
    // Pindahkan gravity dan jumpForce ke private
    float gravity;
    float jumpForce;
    
public:
    Bird();
    void SetTexture(Texture2D tex); // Tambahkan deklarasi ini
    void Update();
    void Draw() const;
    Rectangle GetRect() const;
    void Jump();
    bool CheckCollision(const Pipe& pipe) const;
};