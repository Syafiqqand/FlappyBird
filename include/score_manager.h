//Observer

#pragma once
#include "game_manager.h"
#include <raylib.h> 

class ScoreManager : public Observer {
    int score = 0;
public:
    void OnNotify(int event) override;
    void Draw() const;
    void Reset();      
    int  GetScore() const; 
};
