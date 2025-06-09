#pragma once
#include "pipe.h"
#include <raylib.h>

class PipeFactory {
public:
    static Pipe CreatePipe(int screenWidth, int screenHeight,
                           Texture2D tex,
                           float minGapHeight, float maxGapHeight,
                           float desiredWidth);

    // Tambahan fungsi accessor
    static int GetRandomSpawnInterval();
    static float GetMinGapHeight();
    static float GetMaxGapHeight();
};

