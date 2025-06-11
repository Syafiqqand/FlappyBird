#include "include/score_manager.h"
#include <raylib.h>

void ScoreManager::OnNotify(int event) {
    if (event == 1) {
        score += 1;
    }
}

void ScoreManager::Draw() const {
    DrawText(
        TextFormat("Score: %d", score),
        30, 30, 50, WHITE
    );
}

void ScoreManager::Reset() {
    score = 0;
}

int ScoreManager::GetScore() const {
    return score;
}
