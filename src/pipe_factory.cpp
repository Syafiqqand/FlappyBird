#include "include/pipe_factory.h"
#include <raylib.h>

Pipe PipeFactory::CreatePipe(int screenWidth, int screenHeight,
                             Texture2D tex,
                             float minGapHeight, float maxGapHeight,
                             float desiredWidth)  // <-- di sini
{
    // (1) Randomize tinggi gap antara minGapHeight..maxGapHeight
    float gapHeight = static_cast<float>(
        GetRandomValue((int)minGapHeight, (int)maxGapHeight)
    );

    // (2) Hitung posisi Y dari gap (batas atas/bawah)
    float groundMargin = 50.0f;
    float maxGapY = screenHeight - gapHeight - groundMargin;
    float minGapY =  50.0f;
    float gapY = static_cast<float>(
        GetRandomValue((int)minGapY, (int)maxGapY)
    );

    // (3) Kembalikan Pipe dengan desiredWidth yang diteruskan
    return Pipe(
        static_cast<float>(screenWidth),
        gapY,
        gapHeight,
        tex,
        desiredWidth      // <-- pakai parameter ini
    );
}
