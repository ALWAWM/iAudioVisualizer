// avaudio.cpp
#include "avaudio.h"
#include "commonheaders.h"

AVAudio::AVAudio(std::string musicPath, float defaultVolume, std::string musicName)
    : musicPath(musicPath), volume(defaultVolume) {
    //std::cout<<"音乐加载中"<<std::endl;
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
    if (musicName.empty()){
        // 将string转换为path对象
        std::filesystem::path pathObj(musicPath);
        // 获取文件名（不包括扩展名）
        this->musicName = pathObj.stem().string();
    }
}

AVAudio::~AVAudio() = default;

std::vector<float> AVAudio::analyzeFrequency(const std::vector<float>& audioSamples) {
    int N = audioSamples.size();
    int paddedN = 1;
    while (paddedN < N / 1000) {
        paddedN <<= 1;
    }
    std::cout<<paddedN<<std::endl;
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

std::vector<float> AVAudio::getAudioSamples() {
    sf::SoundBuffer buffer = this->buffer;

    const sf::Int16* samples = buffer.getSamples();
    std::size_t sampleCount = buffer.getSampleCount();
    std::vector<float> audioSamples(sampleCount);

    for (std::size_t i = 0; i < sampleCount; ++i) {
        audioSamples[i] = static_cast<float>(samples[i]) / std::numeric_limits<sf::Int16>::max();
    }

    return audioSamples;
}

//*/
std::string AVAudio::getMusicName() const {
    return musicName;
}

std::wstring AVAudio::getWideMusicName() const {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideMusicName = converter.from_bytes(this->musicName);
    return wideMusicName;
}

std::string AVAudio::getMusicPath() const {
    return musicPath;
}

void AVAudio::setMusicName(std::string newName) {
    this->musicName = newName;
}
void AVAudio::setMusicPath(std::string newPath) {
    this->musicPath = newPath;
}

void AVAudio::setVolume(){
    this->music.setVolume(this->volume);
}



