#pragma once 
#include "commonheaders.h"
/**
 * loadException类。
 * 
 * 该类继承自std::exception，用于处理加载异常。
 */
class loadException : public std::exception {
public:
    /**
     * loadException类的构造函数。
     * 
     * 该构造函数接受一个字符串参数，用于初始化异常消息。
     * 
     * @param message 异常消息。
     */
    loadException(const std::string& file,const std::string& filetype) : file(file) {}
    /**
     * what()函数，用于获取异常消息。
     * 
     * 该函数返回一个指向异常消息的常量字符指针。
     * 
     * @return 指向异常消息的常量字符指针。
     */
    const char* what() const noexcept override {
        std::string message = "Could not load \"" + filetype + "\" file: \"" + file +"\"";
        return message.c_str();
    }
private:
    std::string file;
    std::string filetype;
};

class customException : public std::exception {
public:
    customException(const std::string& message) : message(message) {}
    const char* what() const noexcept override {
        // 返回异常消息的C风格字符串表示
        return message.c_str();
    }
private:
    std::string message;
};

/**
 * AVAudio类。
 * 
 * 该类封装了音乐文件的处理和分析功能等。
 */
class AVAudio {
public:
    /**
     * 分析音频样本的频率分量。
     * 
     * 该函数对输入的音频样本进行快速傅里叶变换（FFT），以提取频率信息。
     * 它使用KissFFT库来执行FFT，并返回一个包含每个频率分量幅度的向量。
     * 
     * @param audioSamples 包含音频样本的向量。
     * @return 包含每个频率分量幅度的向量。
     */
    std::vector<float> analyzeFrequency(const std::vector<float>& audioSamples) {
        // 获取音频样本的数量
        int N = audioSamples.size();
        // 计算用于FFT的填充长度，确保其为2的幂
        int paddedN = 1;
        while (paddedN < N) {
            paddedN <<= 1;
        }

        // 创建输入和输出的复数向量，用于FFT
        std::vector<kiss_fft_cpx> in(paddedN);
        std::vector<kiss_fft_cpx> out(paddedN);

        // 将音频样本填充到输入向量中
        for (int i = 0; i < N; ++i) {
            in[i].r = audioSamples[i];
            in[i].i = 0;
        }
        // 用零填充剩余的输入向量
        for (int i = N; i < paddedN; ++i) {
            in[i].r = 0;
            in[i].i = 0;
        }

        // 分配KissFFT配置
        kiss_fft_cfg cfg = kiss_fft_alloc(paddedN, 0, nullptr, nullptr);
        if (!cfg) {
            std::cerr << "Failed to allocate KissFFT configuration." << std::endl;
            return {};
        }

        // 执行FFT
        kiss_fft(cfg, in.data(), out.data());

        // 创建一个向量来存储幅度
        std::vector<float> magnitudes(paddedN / 2 + 1);
        // 计算每个频率分量的幅度
        for (int i = 0; i <= paddedN / 2; ++i) {
            magnitudes[i] = std::sqrt(out[i].r * out[i].r + out[i].i * out[i].i);
        }

        // 释放KissFFT配置
        kiss_fft_free(cfg);

        // 返回幅度向量
        return magnitudes;
    }

    /**
     * AVAudio类的构造函数。
     * 
     * @param musicName 音乐的名称。
     * @param musicPath 音乐文件的路径。
     */
    AVAudio(std::string musicName, std::string musicPath):musicName(musicName),musicPath(musicPath)  {// 构造函数
        try{
            // 尝试从文件路径中打开音乐文件
            if (!music.openFromFile(musicPath)) {
                throw loadException(musicPath,"music");
            }
            // 尝试从文件路径中加载音乐文件到缓冲区
            if (!buffer.loadFromFile(musicPath)) {
                throw loadException(musicPath,"buffer");
            }
        }
        catch(const loadException& e){
            std::cerr << e.what() << std::endl;
        }
    }
    /**
     * 播放音乐。
     * 
     * 该函数调用SFML库中的`play`方法来播放音乐。
     */
    void play() {
        music.play();
    }
    /**
     * 暂停音乐。
     *
     * 该函数调用SFML库中的`pause`方法来暂停音乐。
     */
    void pause() {
        music.pause();
    }
    /**
     * 停止音乐。
     *
     * 该函数调用SFML库中的`stop`方法来停止音乐。
     */
    void stop() {
        music.stop();
    }

    /**
     * 获取音乐名称。
     * 
     * 该函数返回一个字符串，表示音乐的名称。
     * 
     * @return 音乐的名称。
     */
    std::string getMusicName() const {
        return musicName;
    }

    /**
     * 获取音乐文件路径。
     * 
     * 该函数返回一个字符串，表示音乐文件的路径。
     * 
     * @return 音乐文件的路径。
     */
    std::string getMusicPath() const {
        return musicPath;
    }

    // 变量
    // 音乐
    sf::Music music;
    // Buffer
    sf::SoundBuffer buffer;
private:
    // 音乐名称
    std::string musicName;
    // 音乐文件路径
    std::string musicPath;
};