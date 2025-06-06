#pragma once
#include <raylib.h>

class Pipe {
public:
    // Collider bagian atas dan bawah
    Rectangle upper;
    Rectangle lower;
    bool passed = false;

    // --- Variabel animasi ---
    Texture2D texture;      // spritesheet obstacle
    Rectangle frameRec;     // rectangle frame di spritesheet
    int     currentFrame;   // indeks frame animasi (0..maxFrames-1)
    int     framesCounter;  // counter untuk timing animasi
    int     framesSpeed;    // kecepatan animasi (frame per second)
    int     maxFrames;      // total frame (4×3 = 12)
    int     cols, rows;     // kolom dan baris spritesheet
    float   frameWidth;     // lebar asli satu frame (pixel)
    float   frameHeight;    // tinggi asli satu frame (pixel)

    // --- Scaling & ukuran gap ---
    float   desiredWidth;   // lebar sprite (set misalnya 80 px)
    float   scale;          // faktor scaling = desiredWidth / frameWidth
    float   gapHeight;      // jarak vertikal antara pipa atas & bawah

    // Konstruktor baru: terima posisi X, posisi Y gap (gapY), tinggi gap (gapHeight),
    // texture spritesheet, dan desiredWidth
    Pipe(float x, float gapY, float _gapHeight, Texture2D tex, float _desiredWidth);

    void Update();
    void Draw() const;
    bool IsOffScreen() const;
};
