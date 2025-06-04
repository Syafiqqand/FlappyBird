#include "include/pipe.h"
#include <raylib.h>

Pipe::Pipe(float x, float gapY) {
    const float width = 80;
    const float gapHeight = 200;

    upper = { x, 0, width, gapY };
    lower = { x, gapY + gapHeight, width, GetScreenHeight() - gapY - gapHeight };
}

void Pipe::Update() {
    upper.x -= 2;
    lower.x -= 2;
}

void Pipe::Draw() const {
    DrawRectangleRec(upper, RED);
    DrawRectangleRec(lower, RED);
}

bool Pipe::IsOffScreen() const {
    return (upper.x + upper.width < 0);
}
