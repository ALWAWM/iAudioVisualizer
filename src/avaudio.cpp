#include "avaudio.h"
#include <iostream>
#include <cmath>

AVAudio::AVAudio(std::string musicName, std::string musicPath)
    : musicName(musicName), musicPath(musicPath) {
    try {
        if (!music.openFromFile(musicPath)) {
            throw loadException(musicPath, "music");
        }
        if (!buffer.loadFromFile(musicPath)) {
            throw loadException(musicPath, "buffer");
        }
    } catch (const loadException& e) {
        std::cerr << e.what() << std::endl;
    }
}


std::vector<float> AVAudio::analyzeFrequency(const std::vector<float>& audioSamples) {
    int N = audioSamples.size();
    int paddedN = 1;
    while (paddedN < N) {
        paddedN <<= 1;
    }

    std::vector<kiss_fft_cpx> in(paddedN);
    std::vector<kiss_fft_cpx> out(paddedN);

    for (int i = 0; i < N; ++i) {
        in[i].r = audioSamples[i];
        in[i].i = 0;
    }
    for (int i = N; i < paddedN; ++i) {
        in[i].r = 0;
        in[i].i = 0;
    }

    kiss_fft_cfg cfg = kiss_fft_alloc(paddedN, 0, nullptr, nullptr);
    if (!cfg) {
        std::cerr << "Failed to allocate KissFFT configuration." << std::endl;
        return {};
    }

    kiss_fft(cfg, in.data(), out.data());

    std::vector<float> magnitudes(paddedN / 2 + 1);
    for (int i = 0; i <= paddedN / 2; ++i) {
        magnitudes[i] = std::sqrt(out[i].r * out[i].r + out[i].i * out[i].i);
    }

    kiss_fft_free(cfg);

    return magnitudes;
}
//*/
std::string AVAudio::getMusicName() const {
    return musicName;
}

std::string AVAudio::getMusicPath() const {
    return musicPath;
}