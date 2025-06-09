#include "include/pipe.h"
#include <raylib.h>

Pipe::Pipe(float x, float gapY, float _gapHeight, Texture2D tex, float _desiredWidth)
    : texture(tex),
      currentFrame(0),
      framesCounter(0),
      framesSpeed(8),    
      maxFrames(12),
      cols(4), rows(3),
      desiredWidth(_desiredWidth),
      gapHeight(_gapHeight)
{
    // Hitung ukuran asli tiap frame di spritesheet
    frameWidth  = static_cast<float>(texture.width)  / static_cast<float>(cols);
    frameHeight = static_cast<float>(texture.height) / static_cast<float>(rows);

    // Hitung faktor scale agar lebar frame menjadi desiredWidth
    scale = desiredWidth / frameWidth;

    frameRec = { 0.0f, 0.0f, frameWidth, frameHeight };

    upper = { x, 0.0f, desiredWidth, gapY };
    lower = { x, gapY + gapHeight, desiredWidth, GetScreenHeight() - gapY - gapHeight };
}

void Pipe::Update() {
    // 1) Animasi frame
    framesCounter++;
    if (framesCounter >= (60 / framesSpeed)) {
        framesCounter = 0;
        currentFrame++;
        if (currentFrame >= maxFrames) currentFrame = 0;

        // Hitung baris & kolom frame saat ini
        int frameX = currentFrame % cols;  // 0..3
        int frameY = currentFrame / cols;  // 0..2
        frameRec.x = frameX * frameWidth;
        frameRec.y = frameY * frameHeight;
    }

    // 2) Gerakkan pipa ke kiri (2 px per frame)
    upper.x -= 2.0f;
    lower.x -= 2.0f;
}

void Pipe::Draw() const {
    // --- Gambar pipa bawah (tanpa rotasi) ---
    Rectangle destRecBot = {
        lower.x,         // posX
        lower.y,         // posY
        desiredWidth,    // lebar → width sprite setelah scale
        lower.height     // tinggi → sama dengan height collider
    };
    DrawTexturePro(
        texture,
        frameRec,
        destRecBot,
        { 0.0f, 0.0f },  // origin di sudut kiri-atas
        0.0f,            // rotasi 0°
        WHITE
    );

    // --- Gambar pipa atas (flip 180°) ---
    // Kita perlu meletakkan origin di tengah destRecTop agar pas saat rotasi
    Rectangle destRecTop = {
        upper.x + (desiredWidth * 0.5f),      // posX + originX
        upper.y + (upper.height * 0.5f),      // posY + originY
        desiredWidth,                         // lebar
        upper.height                          // tinggi
    };
    Vector2 originFlip = { desiredWidth * 0.5f, upper.height * 0.5f };

    DrawTexturePro(
        texture,
        frameRec,
        destRecTop,
        originFlip,
        180.0f,    // rotasi 180° agar sprite terbalik
        WHITE
    );
}

bool Pipe::IsOffScreen() const {
    return (upper.x + upper.width < 0);
}
