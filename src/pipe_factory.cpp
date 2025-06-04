#include "include/pipe_factory.h"
#include <raylib.h>

Pipe PipeFactory::CreatePipe(int screenWidth, int screenHeight) {
    const int gapHeight = 200;
    int gapY = GetRandomValue(100, screenHeight - gapHeight - 100);
    return Pipe(screenWidth + 50, gapY);
}
