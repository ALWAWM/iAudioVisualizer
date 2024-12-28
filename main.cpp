//
//  main.cpp
//  iAudioVisualizer(iAV)
//
//  Created by ALWAWM on 28/12/2024.
//  Copyright © 2024 ALWAWM. All rights reserved.
//
//  This is the main file of the project.
//  The project is a simple audio visualizer.
//  The project is based on the SFML library.
//  The project is using the C++17 language standard.
//  
#define version 1.0
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "include/allheaders.h"
int main(){
    #ifdef _WIN32
        std::cout << "Operating System: Windows" << std::endl;
    #elif defined(__linux__)
        std::cout << "Operating System: Linux" << std::endl;
    #elif defined(__APPLE__)
        std::cout << "Operating System: Apple" << std::endl;
        std::cout << __APPLE__ << std::endl;
    #elif defined(__unix__)
        std::cout << "Operating System: Unix" << std::endl;
    #endif



    sf::RenderWindow window(sf::VideoMode(800,600),"iAudioVisualizer (iAV)");
    window.setFramerateLimit(60);
    sf::Music music;
    if (!music.openFromFile("./audio.mp3")) {  // 将这里的文件名替换为实际的音频文件名
        // 如果无法打开文件，进行错误处理，比如输出提示信息并退出程序
        std::cerr << "Could not open audio file" << std::endl;
        return -1;
    }
    music.play();  // 开始播放音频

    // 加载音频文件到 SoundBuffer
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("your_audio_file.mp3")) {
        std::cerr << "Could not load audio file for buffer" << std::endl;
        return -1;
    }
    const sf::Int16* samples = buffer.getSamples();
    std::size_t sampleCount = buffer.getSampleCount();
    // 简单计算音频的平均音量，这里只是示例，可优化
    float sumVolume = 0;
    for (std::size_t i = 0; i < sampleCount; ++i) {
        sumVolume += std::abs(samples[i]);
    }
    float averageVolume = sumVolume / sampleCount;

    // 主循环
    while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    window.clear(sf::Color::Black);  // 先清空窗口，设置背景颜色为黑色

    // 根据音频音量绘制矩形（示例）
    float volumeFactor = averageVolume / 32768.0f;  // 调整音量范围到合适比例，32768 是 Int16 类型样本的最大值
    sf::RectangleShape rectangle(sf::Vector2f(100, 100 * volumeFactor));
    rectangle.setPosition(100, 100);
    rectangle.setFillColor(sf::Color::White);
    window.draw(rectangle);

    window.display();  // 显示绘制的内容
}
}