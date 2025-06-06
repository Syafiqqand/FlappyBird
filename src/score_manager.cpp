#include "include/score_manager.h"
#include <raylib.h>

void ScoreManager::OnNotify(int event) {
    // Misalkan event = 1 artinya "burung berhasil melewati satu pipa".
    // Jadi kita tambahkan satu poin setiap kali OnNotify(1) dipanggil.
    if (event == 1) {
        score += 1;
    }
    // Jika suatu saat ada event lain, bisa di-handle di sini.
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
