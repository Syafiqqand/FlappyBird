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
        
        float fw = static_cast<float>(texture.width) / 5.0f;
        float fh = static_cast<float>(texture.height) / 5.0f;
        frameRec = { 0.0f, 0.0f, fw, fh };
    } else {
        TraceLog(LOG_WARNING, "Bird texture not set!");
    }
}

void Bird::Update() {
    velocity += gravity;
    y += velocity;

    if (y > GetScreenHeight()) {
        y = GetScreenHeight();
        velocity = 0;
    }
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
        frameRec.x = frameX * frameRec.width;
        frameRec.y = frameY * frameRec.height;
    }
}

bool Bird::CheckCollision(const Pipe& pipe) const {
    float r = (frameRec.width < frameRec.height ? frameRec.width/2.0f : frameRec.height/2.0f) * 0.8f;
    Vector2 center = { x, y };
    return CheckCollisionCircleRec(center, r, pipe.upper)
        || CheckCollisionCircleRec(center, r, pipe.lower);
}

void Bird::Jump() {
    velocity = jumpForce;
}

void Bird::Draw() const {
    if (texture.id != 0) {
        Vector2 position = {
            x - frameRec.width / 2.0f,
            y - frameRec.height / 2.0f
        };
        DrawTextureRec(texture, frameRec, position, WHITE);
    } else {
        DrawCircle((int)x, (int)y, 20, RED);
    }
}

Rectangle Bird::GetRect() const {
    return { 
        x - frameRec.width/2.0f, 
        y - frameRec.height/2.0f, 
        frameRec.width, 
        frameRec.height 
    };
}
