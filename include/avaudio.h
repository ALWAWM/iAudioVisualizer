#pragma once

#include "commonheaders.h"
#include "loadexception.h"

class AVAudio {
public:
    AVAudio(std::string musicPath, float defaultVolume = 100.0f, std::string musicName = "");
    ~AVAudio();

    std::vector<float> analyzeFrequency(const std::vector<float>& audioSamples);

std::vector<float> getAudioSamples() ;

    std::string getMusicName() const;
    std::wstring getWideMusicName() const;
    std::string getMusicPath() const;
    void setMusicName(std::string newName);
    void setMusicPath(std::string newPath);
    void setVolume();

    sf::Music music;
    sf::SoundBuffer buffer;
    float volume;
private:
    std::string musicName;
    std::string musicPath;
};