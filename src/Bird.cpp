#include "include/bird.h"
#include "include/pipe.h"
#include <raylib.h>

Bird::Bird() : 
    x(100), y(300), velocity(0),
    currentFrame(0), framesCounter(0), framesSpeed(8),
    gravity(0.5f), jumpForce(-10.0f)
{
    texture = {0};
    frameRec = {0, 0, 0, 0};
}

void Bird::SetTexture(Texture2D tex) {
    texture = tex;
    
    if (texture.id != 0) {
        TraceLog(LOG_INFO, "Bird texture loaded: %dx%d", texture.width, texture.height);
        frameRec = { 
            0.0f, 
            0.0f, 
            static_cast<float>(texture.width) / 5.0f, 
            static_cast<float>(texture.height) / 5.0f 
        };
    } else {
        TraceLog(LOG_WARNING, "Bird texture not set!");
    }
}

void Bird::Update() {
    velocity += gravity;
    y += velocity;

    if (y > GetScreenHeight()) y = GetScreenHeight();
    if (y < 0) {
        y = 0;
        velocity = 0;
    }
    
    framesCounter++;
    if (framesCounter >= (60 / framesSpeed)) {
        framesCounter = 0;
        currentFrame++;
        
        if (currentFrame >= 25) currentFrame = 0;
        
        int frameX = currentFrame % 5;
        int frameY = currentFrame / 5;
        
        frameRec.x = (float)frameX * frameRec.width;
        frameRec.y = (float)frameY * frameRec.height;
    }
}

Rectangle Bird::GetRect() const {
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
    if (texture.id != 0) {
        // Hitung posisi tengah dengan benar
        Vector2 position = {
            x - frameRec.width / 2.0f,
            y - frameRec.height / 2.0f
        };
        
        // Debug: Gambar bounding box
        DrawRectangleLinesEx(
            {position.x, position.y, frameRec.width, frameRec.height},
            2,
            RED
        );
        
        DrawTextureRec(texture, frameRec, position, WHITE);
    } else {
        DrawRectangleRec(GetRect(), RED);
    }
}