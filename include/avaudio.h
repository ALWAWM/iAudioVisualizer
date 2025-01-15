#pragma once

#include "commonheaders.h"
#include "loadexception.h"

class AVAudio {
public:
    AVAudio(std::string musicName, std::string musicPath);

    std::vector<float> analyzeFrequency(const std::vector<float>& audioSamples);

    std::string getMusicName() const;
    std::string getMusicPath() const;

    sf::Music music;
    sf::SoundBuffer buffer;

private:
    std::string musicName;
    std::string musicPath;
};