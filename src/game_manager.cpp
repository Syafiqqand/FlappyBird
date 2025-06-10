#include "include/game_manager.h"
#include <vector>

void GameManager::Attach(Observer* observer) {
    observers.push_back(observer);
}

void GameManager::Notify(int event) {
    for (auto obs : observers) {
        obs->OnNotify(event);
    }
}

void GameManager::AddScore(int value) {
    score += value;
    Notify(score);
}

int GameManager::GetScore() const {
    return score;
}

GameState GameManager::GetState() const {
    return state;
}

void GameManager::SetState(GameState newState) {
    state = newState;
}

void GameManager::Reset() {
    score = 0;
    state = PLAYING;
    Notify(score);
}
