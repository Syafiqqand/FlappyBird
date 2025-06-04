#pragma once
#include <vector>
#include <algorithm>

enum GameState {
    MENU,       
    PLAYING,
    GAME_OVER
};

class Observer {
public:
    virtual void OnNotify(int event) = 0;
    virtual ~Observer() = default;
};

class GameManager {
    std::vector<Observer*> observers;
    int score = 0;
    GameState state = PLAYING;
public:
    void Attach(Observer* observer);
    void Notify(int event);
    void AddScore(int value);
    int GetScore() const;
    GameState GetState() const;
    void SetState(GameState newState);
    void Reset();
};