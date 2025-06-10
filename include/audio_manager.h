#pragma once
#include <raylib.h>

class AudioManager {
private:
    static AudioManager* instance;
    Music bgMusic;
    Sound jumpSound;
    Sound scoreSound;
    Sound crashSound;
    
    // Constructor private
    AudioManager() {}

public:
    static AudioManager* getInstance() {
        if (instance == nullptr) {
            instance = new AudioManager();
        }
        return instance;
    }

    void Initialize() {
        InitAudioDevice();
        LoadAllSounds();
    }

    void LoadAllSounds() {
        bgMusic = LoadMusicStream("best-game-console-301284.mp3");
        jumpSound = LoadSound("jump.mp3");
        scoreSound = LoadSound("score.mp3");
        crashSound = LoadSound("crash.mp3");
        SetMusicVolume(bgMusic, 0.5f);
    }

    void PlayBackgroundMusic() {
        PlayMusicStream(bgMusic);
    }

    void PlayJumpSound() {
        PlaySound(jumpSound);
    }

    void PlayScoreSound() {
        PlaySound(scoreSound);
    }

    void PlayCrashSound() {
        PlaySound(crashSound);
    }

    void Update() {
        UpdateMusicStream(bgMusic);
    }

    void Cleanup() {
        UnloadMusicStream(bgMusic);
        UnloadSound(jumpSound);
        UnloadSound(scoreSound);
        UnloadSound(crashSound);
        CloseAudioDevice();
    }
};