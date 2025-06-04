#include "include/bird.h"
#include "include/pipe.h"
#include <raylib.h>

Bird::Bird() : 
    x(100), y(300), velocity(0),
    currentFrame(0), framesCounter(0), framesSpeed(8)
{
    // Inisialisasi default
}

texture = tex;
    // Asumsikan sprite sheet memiliki 4 frame horizontal
    frameRec = { 
        0.0f, 
        0.0f, 
        static_cast<float>(texture.width) / 4.0f, 
        static_cast<float>(texture.height) 
    };

void Bird::Update() {
    velocity += gravity;
    y += velocity;

    if (y > GetScreenHeight()) y = GetScreenHeight();
    if (y < 0) y = 0;
    
    // Animasi frame
    framesCounter++;
    if (framesCounter >= (60 / framesSpeed)) {
        framesCounter = 0;
        currentFrame++;
        
        // Loop animasi (asumsikan 4 frame)
        if (currentFrame > 3) currentFrame = 0;
        
        frameRec.x = (float)currentFrame * (float)texture.width/4;
    }
}

Rectangle Bird::GetRect() const {
    // Sesuaikan ukuran dengan frame animasi
    return { 
        x - frameRec.width/2, 
        y - frameRec.height/2, 
        frameRec.width, 
        frameRec.height 
    };
}

bool Bird::CheckCollision(const Pipe& pipe) const {
    return CheckCollisionRecs(GetRect(), pipe.upper) ||
           CheckCollisionRecs(GetRect(), pipe.lower);
}

void Bird::Jump() {
    velocity = jumpForce;
}

void Bird::Draw() const {
    if (texture.id != 0) { // Pastikan texture valid
        DrawTextureRec(
            texture, 
            frameRec, 
            { 
                x - frameRec.width / 2.0f, 
                y - frameRec.height / 2.0f 
            }, 
            WHITE
        );
    } else {
        // Fallback jika texture tidak load
        DrawRectangleRec(GetRect(), RED);
    }
}