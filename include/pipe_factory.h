#pragma once
#include "pipe.h"

class PipeFactory {
public:
    static Pipe CreatePipe(int screenWidth, int screenHeight);
};