#include "include/pipe_factory.h"
#include <raylib.h>

// === Interval dan tinggi gap default ===
const int   MIN_SPAWN_INTERVAL = 200;
const int   MAX_SPAWN_INTERVAL = 350;

const float MIN_GAP_HEIGHT = 300.0f;
const float MAX_GAP_HEIGHT = 450.0f;

int PipeFactory::GetRandomSpawnInterval() {
    return GetRandomValue(MIN_SPAWN_INTERVAL, MAX_SPAWN_INTERVAL);
}

float PipeFactory::GetMinGapHeight() {
    return MIN_GAP_HEIGHT;
}

float PipeFactory::GetMaxGapHeight() {
    return MAX_GAP_HEIGHT;
}

Pipe PipeFactory::CreatePipe(int screenWidth, int screenHeight,
                             Texture2D tex,
                             float minGapHeight, float maxGapHeight,
                             float desiredWidth)
{
    // (1) Randomize tinggi gap antara minGapHeight..maxGapHeight
    float gapHeight = static_cast<float>(
        GetRandomValue((int)minGapHeight, (int)maxGapHeight)
    );

    // (2) Hitung posisi Y dari gap (batas atas/bawah)
    float groundMargin = 50.0f;
    float maxGapY = screenHeight - gapHeight - groundMargin;
    float minGapY = 50.0f;
    float gapY = static_cast<float>(
        GetRandomValue((int)minGapY, (int)maxGapY)
    );

    // (3) Kembalikan Pipe dengan desiredWidth yang diteruskan
    return Pipe(
        static_cast<float>(screenWidth),
        gapY,
        gapHeight,
        tex,
        desiredWidth
    );
}
