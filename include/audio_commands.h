#pragma once
#include "audio_manager.h"

enum SoundType {
    JUMP,
    SCORE,
    CRASH
};

class AudioCommand {
public:
    virtual void execute() = 0;
    virtual ~AudioCommand() {}
};

class PlayMusicCommand : public AudioCommand {
public:
    void execute() override {
        AudioManager::getInstance()->PlayBackgroundMusic();
    }
};

class PlaySoundCommand : public AudioCommand {
private:
    SoundType type;
public:
    PlaySoundCommand(SoundType t) : type(t) {}
    void execute() override {
        switch(type) {
            case JUMP:
                AudioManager::getInstance()->PlayJumpSound();
                break;
            case SCORE:
                AudioManager::getInstance()->PlayScoreSound();
                break;
            case CRASH:
                AudioManager::getInstance()->PlayCrashSound();
                break;
        }
    }
};