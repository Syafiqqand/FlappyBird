#pragma once
#include "pipe.h"
#include <raylib.h>

class PipeFactory {
public:
    // Tambahkan float desiredWidth di parameter terakhir
    static Pipe CreatePipe(int screenWidth, int screenHeight,
                           Texture2D tex,
                           float minGapHeight, float maxGapHeight,
                           float desiredWidth);
};
