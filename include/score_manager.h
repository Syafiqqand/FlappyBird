//Observer

#pragma once
#include "game_manager.h"
#include <raylib.h>  // Pastikan Raylib di-include

class ScoreManager : public Observer {
    int score = 0;
public:
    void OnNotify(int event) override;
    void Draw() const;
    void Reset();      // Tambahkan method untuk mereset skor
    int  GetScore() const; // Jika diperlukan di tempat lain
};
