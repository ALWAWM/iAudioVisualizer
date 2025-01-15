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
#define i_Audio_Visualizer 1
#define iAV 1
#define iAudioVisualizer 1  
#define iAV_Ver "0.2.1"
unsigned int main_window_x_size = 1080u;
unsigned int main_window_y_size = 720u;

#include "allheaders.h"

using namespace std;

string music_file = "./audio.mp3";
string image_file = "./image.jpg";
string ini_file = "conf.ini";

// 解析版本号字符串
tuple<int, int, int> parseVersion(const string& version) {
    int major = 0, minor = 0, patch = 0;
    sscanf(version.c_str(), "%d.%d.%d", &major, &minor, &patch);
    return make_tuple(major, minor, patch);
}
// 比较版本号
bool isVersionGreater(const string& version1, const string& version2) {
    auto [major1, minor1, patch1] = parseVersion(version1);
    auto [major2, minor2, patch2] = parseVersion(version2);

    if (major1 != major2) return major1 > major2;
    if (minor1 != minor2) return minor1 > minor2;
    return patch1 <= patch2;
}
// 解析INI文件的回调函数
int iniHandler(void* user, const char* section, const char* name, const char* value) {
    string* music_file = static_cast<string*>(user);

    if (strcmp(section, "Audio") == 0 && strcmp(name, "music_file") == 0) {
        *music_file = value;
    } else if (strcmp(section, "Image") == 0 && strcmp(name, "image_file") == 0) {
        image_file = value;
    }
    return 1;
}
// 打印帮助信息
void printHelp() {
    cout << "Usage: iAudioVisualizer [options]" << endl;
    cout << "Options:" << endl;
    cout << "  -c, --config <file>   Specify the INI configuration file" << endl;
    cout << "  -h, --help            Display this help message" << endl;
    cout << "  -v, --version         Print software version" << endl;
}
// 主函数
int main(int argc, char* argv[]) {
    // 解析命令行参数
    int opt;
    struct option long_options[] = {
        {"config", required_argument, 0, 'c'},
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };
    while ((opt = getopt_long(argc, argv, "m:i:c:h:v", long_options, nullptr)) != -1) {
        switch (opt) {
            case 'c':
                ini_file = optarg;
                break;
            case 'h':
                printHelp();
                return 0;
            case 'v':
                cout<<"Version:"<<iAV_Ver<<endl;
                break;
            default:
                printHelp();
                return 1;
        }
    }
    try{
        // 解析INI文件
        if (ini_parse(ini_file.c_str(), iniHandler, &music_file) < 0) {
                throw loadException(ini_file,"INI");
        }
    }catch(loadException& e){
        cerr<<e.what()<<endl;
        return 1;
    }
    // 创建窗口
    sf::RenderWindow window(sf::VideoMode(main_window_x_size, main_window_y_size), "iAudioVisualizer (iAV)");
    window.setFramerateLimit(60);
    

    // 创建音乐
    AVAudio audio(music_file, music_file);
    audio.music.play();
    
    const sf::Int16* samples = audio.buffer.getSamples();
    std::size_t sampleCount = audio.buffer.getSampleCount();
    unsigned int sampleRate = audio.buffer.getSampleRate();
    unsigned int channelCount = audio.buffer.getChannelCount();

    // 存储音频样本数据
    std::vector<sf::Int16> audioSamples(samples, samples + sampleCount);


    // 创建一个滑块
    sf::RectangleShape sliderBackground(sf::Vector2f(main_window_x_size/2, 20));
    sliderBackground.setFillColor(sf::Color(255,255,255,40));
    sliderBackground.setPosition(sfcentershape(window,sliderBackground).x, 10);

    sf::RectangleShape sliderHandle(sf::Vector2f(10, 20));
    sliderHandle.setFillColor(sf::Color::Red);
    sliderHandle.setPosition(sfcentershape(window,sliderHandle).x, 10);


    // 主循环
    while (window.isOpen()) {
        srand(time(0)+rand());  // 生成随机数种子
        sf::Event event;// 声明一个 sf::Event 对象，用于存储窗口事件
        // 循环处理窗口事件
        while (window.pollEvent(event)) {
            sfwindowclose(window, event);  // 检查并关闭 SFML 窗口

            // 处理滑块事件
            // 检查是否有鼠标按钮被按下
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Mouse button pressed at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
                // 检查鼠标是否在滑块手柄上
                if (sliderHandle.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    audio.music.pause();  // 暂停音频播放
                    // 如果鼠标在滑块手柄上，将滑块手柄颜色设置为蓝色
                    sliderHandle.setFillColor(sf::Color::Blue);
                    std::cout << "Mouse button pressed on slider handle at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
                }
            }
            // 检查是否有鼠标按钮被释放
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                if (audio.music.getStatus() != sf::Music::Playing) {
                    audio.music.play();  // 恢复音频播放
                }
                // 如果鼠标按钮被释放，将滑块手柄颜色设置为红色
                sliderHandle.setFillColor(sf::Color::Red);
                std::cout << "Mouse button released" << std::endl;
            }

            // 检查鼠标是否移动
            else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // 检查鼠标是否在滑块背景上
                if (sliderBackground.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                    // 计算滑块手柄的新位置
                    float newX = event.mouseMove.x - sliderHandle.getSize().x / 2;
                    // 确保滑块手柄不会超出滑块背景的左侧
                    if (newX < sliderBackground.getPosition().x) {
                        newX = sliderBackground.getPosition().x;
                    }
                    // 确保滑块手柄不会超出滑块背景的右侧
                    else if (newX + sliderHandle.getSize().x > sliderBackground.getPosition().x + sliderBackground.getSize().x) {
                        newX = sliderBackground.getPosition().x + sliderBackground.getSize().x - sliderHandle.getSize().x;
                    }
                    // 设置滑块手柄的新位置
                    sliderHandle.setPosition(newX, sliderHandle.getPosition().y);
                    std::cout << "Slider handle moved to (" << newX << ", " << sliderHandle.getPosition().y << ")" << std::endl;
                    // 根据滑块位置更新音频播放位置
                    float sliderPercentage = (sliderHandle.getPosition().x - sliderBackground.getPosition().x) / sliderBackground.getSize().x;
                    sf::Time newTime = audio.music.getDuration() * sliderPercentage;
                    audio.music.setPlayingOffset(newTime);
                    std::cout << "Audio playing offset set to " << newTime.asSeconds() << " seconds" << std::endl;
                }
            }

            // 检查是否按下空格键
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (audio.music.getStatus() == sf::Music::Playing) {
                    audio.music.pause();  // 暂停音频播放
                    std::cout << "Music paused" << std::endl;
                } else if (audio.music.getStatus() != sf::Music::Playing) {
                    audio.music.play();  // 恢复音频播放
                    std::cout << "Music resumed" << std::endl;
                }
            }
        }
        // 如果鼠标没有按下，更新滑块位置以匹配音乐播放位置
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            float sliderPercentage = audio.music.getPlayingOffset().asSeconds() / audio.music.getDuration().asSeconds();
            float newX = sliderBackground.getPosition().x + sliderPercentage * sliderBackground.getSize().x - sliderHandle.getSize().x / 2;
            sliderHandle.setPosition(newX, sliderHandle.getPosition().y);
        }
        
        
        // 加载图片
        sf::Texture imageTexture;
        if (!imageTexture.loadFromFile(image_file)) {
            throw std::runtime_error("Failed to load image file");
        }
        sf::Sprite sprite(imageTexture);

        // 获取窗口和图片的大小
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2u textureSize = imageTexture.getSize();

        // 计算缩放比例
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.x) / textureSize.y;

        // 设置缩放比例
        sprite.setScale(scaleX, scaleY);

        // 设置图片位置
        sprite.setPosition(0, 0);

        sprite.setColor(sf::Color(255, 255, 255, 128));  // 设置图片透明度为 128

        // 根据实时音量绘制图形
        // 获取当前播放位置
        sf::Time currentTime = audio.music.getPlayingOffset();
        std::size_t currentSample = static_cast<std::size_t>(currentTime.asSeconds() * sampleRate * channelCount);
        float currentVolume = 0;
        std::size_t sampleWindow = 1024;

        // 计算当前音量
        for (std::size_t i = 0; i < sampleWindow && (currentSample + i) < sampleCount; ++i) {
            currentVolume += std::abs(samples[currentSample + i]);
        }
        currentVolume /= sampleWindow;
        // 调整音量范围到合适比例
        float volumeFactor = currentVolume / 16384.0f;  
        //clog<<"真实音量："<<currentVolume<<"调整后："<<volumeFactor<<endl;
        
        // 根据实时音量绘制矩形
        sf::RectangleShape rectangle(sf::Vector2f(4, 150 * volumeFactor + 1));
        rectangle.setRotation(180);
        // 设置矩形的位置，使其在窗口中居中，并将其水平位置向右移动一个矩形的宽度
        rectangle.setPosition(sfcentershape(window, rectangle).x + rectangle.getGlobalBounds().width, main_window_y_size);
        rectangle.setFillColor(sf::Color::Magenta);  // 设置矩形颜色为紫色

        // 根据实时音量绘制圆形
        sf::CircleShape circle(90 * volumeFactor + main_window_x_size / 8 + rand() % 5 * volumeFactor);
        circle.setPosition(sfcentershape(window,circle).x, sfcentershape(window,circle).y);// 设置圆形位置
        circle.setFillColor(sf::Color::Magenta); 
        // 绘制带有纹理的圆形
        sf::CircleShape circleHasTexture(70 * volumeFactor + main_window_x_size / 8);
        circleHasTexture.setPosition(sfcentershape(window,circleHasTexture).x, sfcentershape(window,circleHasTexture).y);// 设置圆形位置
        circleHasTexture.setFillColor(sf::Color::White);
        circleHasTexture.setTexture(&imageTexture); 

        {// 绘图
            // 绘图前先清空窗口，设置背景颜色为黑色
            window.clear(sf::Color(0,0,0,0));  
            // 绘制图片
            window.draw(sprite);
            // 绘制滑块
            window.draw(sliderBackground);
            window.draw(sliderHandle);

            {// 绘制矩形
                window.draw(rectangle);
                // 向右移动的距离为一个矩形的宽度加上 3 个像素
                for (int i = 2; i <= 142; i++){
                    rectangle.setPosition(sfcentershape(window, rectangle).x + rectangle.getGlobalBounds().width * i + 1 * (i - 1) , main_window_y_size + rand() % 10 * volumeFactor);
                    rectangle.setFillColor(sf::Color(255, 0, 200, 255));
                    window.draw(rectangle);
                }
                // 向左移动
                for (int i = 0; i <= 140; i++){
                    rectangle.setPosition(sfcentershape(window, rectangle).x - rectangle.getGlobalBounds().width * i - 1 * (i + 1), main_window_y_size  + rand() % 10 * volumeFactor);
                    rectangle.setFillColor(sf::Color(255, 0, 200, 255));
                    window.draw(rectangle);
                }
            }
            window.draw(circle);
            window.draw(circleHasTexture);
            window.display();  // 显示绘制的内容
        }
        
    }

    return 0;
} 