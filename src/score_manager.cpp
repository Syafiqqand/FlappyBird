#include "include/score_manager.h"
#include <raylib.h>

void ScoreManager::OnNotify(int event) {
    score = event;
}

void ScoreManager::Draw() const {
    DrawText(
        TextFormat("Score: %d", score),
        10, 10, 30, WHITE
    );
}
