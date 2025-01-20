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

#include "allheaders.h"

#ifdef __APPLE__
    //MacOS平台,库正确时可以正常编译运行
    #pragma optimize("g", on)  // 开启全局优化
#else
    #warning "暂不支持MacOS以外其他平台"
#endif

#define iAV iAV_Ver
#define iAudioVisualizer iAV_Ver 

using namespace std;

struct configuration {
    unsigned int main_window_x_size = 1920u;
    unsigned int main_window_y_size = 1080u;
    sf::Vector2u windowSize = {main_window_x_size, main_window_y_size};
    std::string music_file = "./audio.mp3";
    std::string cover_file = "./image.jpg";
    std::string ini_file = "conf.ini";
    std::string conf_version = "NULL";
    bool mandatory_version_requirement = false;
    sf::View view;
    float default_volume = 100.0f;
    bool shake_effect = true;
}config;

// 解析INI文件的回调函数
int iniHandler(void* user, const char* section, const char* name, const char* value) {
    //configuration* config = static_cast<configuration*>(user);
    if (strcmp(section, "Music") == 0) {
        if (strcmp(name, "MusicFile") == 0){
            config.music_file = value;
        } else if(strcmp(name, "DefaultVolume") == 0){
            config.default_volume = stof(value);
        } else if(strcmp(name, "CoverFile") == 0){
            config.cover_file = value;
        }
    } else if (strcmp(section, "General") == 0) {
        if (strcmp(name, "Version") == 0) {
            config.conf_version = value;
            if (config.conf_version == iAV_Ver) {
                return 1;
            } else if (config.mandatory_version_requirement) {
                goto r_incompatibility;
            }
            if (isVersionInRange(config.conf_version, iAV_Minimum_Compatible_Version, iAV_Ver) || config.conf_version == "*") {
                std::cout << "Warning: Version isn't the same" << std::endl;
                std::cout << "警告: 版本与配置不一致" << std::endl;
            } else {
                std::cerr << config.conf_version << " Version incompatible! Please change the configuration version: " << iAV_Minimum_Compatible_Version << " ~ " << iAV_Ver << std::endl;
                std::cerr << config.conf_version << " 版本不兼容！请更改配置版本：" << iAV_Minimum_Compatible_Version << " ~ " << iAV_Ver << std::endl;
                throw std::runtime_error("Version incompatible");
            }
        } else if (strcmp(name, "MandatoryVersionRequirement") == 0) {
            if (std::string(value) == "true") {
                config.mandatory_version_requirement = true;
                if (config.conf_version != iAV_Ver) {
                    r_incompatibility:
                    std::cerr << "Version incompatibility (configuration requires the same version)!" << std::endl;
                    std::cerr << "版本不兼容（配置强制需要相同版本）!" << std::endl;
                    throw std::runtime_error("Version incompatibility (configuration requires the same version)");
                }
            }
        } else if (strcmp(name, "WindowSize") == 0) {
            sscanf(value, "%ux%u", &config.main_window_x_size, &config.main_window_y_size);
            config.windowSize = {config.main_window_x_size, config.main_window_y_size};
        } 
    } else if(strcmp(section, "Visualizer") == 0){
        if (strcmp(name, "ShakeEffect") == 0){
            if (std::string(value) == "true") {
                config.shake_effect = true;
            } else {
                config.shake_effect = false;
            }

        }
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

void spectrumThreadFunction(AVAudio& audio, vector<float>& spectrumData, std::mutex& spectrumMutex, std::condition_variable& spectrumCV, bool& stopThread) {
    while (!stopThread) {
        // 计算频谱数据
        vector<float> newSpectrumData = audio.analyzeFrequency(audio.getAudioSamples());

        // 更新频谱数据
        {
            std::lock_guard<std::mutex> lock(spectrumMutex);
            spectrumData = std::move(newSpectrumData);
        }

        // 通知主线程频谱数据已更新
        spectrumCV.notify_one();

        // 等待一段时间再进行下一次计算
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void drawSpectrum(const std::vector<float>& magnitudes, sf::RenderWindow& window) {
    // 创建一个顶点数组来存储频谱数据
    sf::VertexArray lines(sf::LinesStrip, magnitudes.size());

    // 设置顶点的位置和颜色
    for (std::size_t i = 0; i < magnitudes.size(); ++i) {
        lines[i].position = sf::Vector2f(static_cast<float>(i), magnitudes[i]);
        lines[i].color = sf::Color::White;
    }

    // 绘制频谱图
    window.draw(lines);
}

// 主函数
int main(int argc, char* argv[]) {
    int indexs=0;
    cout<<"iAV Version:"<<iAV_Ver<<endl;
    // 显示当前运行目录
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "Current working directory: " << currentPath << std::endl;
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
                config.ini_file = optarg;
                break;
            case 'h':
                printHelp();
                return 0;
            case 'v':
                cout<<"Version:"<<iAV_Ver<<endl;
                cout<<"Compile time:"<<__TIME__<<endl;
            default:
                printHelp();
        }
    }
    // 解析INI文件
    try{
        if (ini_parse(config.ini_file.c_str(), iniHandler, &config.music_file) < 0) {
                throw loadException(config.ini_file,"INI");
        }
    }catch(loadException& le){
        cerr<<le.what()<<endl;
        return 1;
    }
    cout<<"正在播放:"<<config.music_file<<endl;
    // 初始化窗口
    sf::RenderWindow window(sf::VideoMode(config.main_window_x_size, config.main_window_y_size), "iAudioVisualizer (iAV)", sf::Style::Close);
    config.view = window.getDefaultView();
    window.setFramerateLimit(60);
    // 加载字体
    sf::Font font;
    if (!font.loadFromFile("./res/STHeiti Medium.ttc")) {
        std::cerr << "无法加载字体文件" << std::endl;
        return -1;
    }

    // 创建音乐
    AVAudio audio(config.music_file);
    audio.music.play();
    audio.volume = config.default_volume;
    audio.setVolume();
    cout<<"音乐加载完成"<<endl;
    
    const sf::Int16* samples = audio.buffer.getSamples();
    std::size_t sampleCount = audio.buffer.getSampleCount();
    unsigned int sampleRate = audio.buffer.getSampleRate();
    unsigned int channelCount = audio.buffer.getChannelCount();

    // 存储音频样本数据
    std::vector<sf::Int16> audioSamples(samples, samples + sampleCount);

    // auto aaaa = audio.getAudioSamples();
    // // 获取当前时间点
    // auto start = std::chrono::high_resolution_clock::now();

    // // 调用函数
    // audio.analyzeFrequency(aaaa);

    // // 获取当前时间点
    // auto end = std::chrono::high_resolution_clock::now();

    // // 计算时间差
    // std::chrono::duration<double> elapsed = end - start;

    // // 输出执行时间
    // std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
    // return 0;

    // 创建一个滑块
    sf::RectangleShape sliderBackground(sf::Vector2f(config.main_window_x_size/2, 20));
    sliderBackground.setFillColor(sf::Color(255,255,255,80));
    sliderBackground.setPosition(sfcentershape(window,sliderBackground).x, 10);

    sf::RectangleShape sliderHandle(sf::Vector2f(10, 20));
    sliderHandle.setFillColor(sf::Color::Red);
    sliderHandle.setPosition(sfcentershape(window,sliderHandle).x, 10);

    // 创建文本对象
    sf::Text text;
    text.setFont(font);
    cout<<"music name:"<<audio.getMusicName()<<endl;
    text.setString(wstring(audio.getWideMusicName())); // 设置中文字符串
    //text.setString(L"你好"); // 设置中文字符串
    srand(time(0));  // 生成随机数种子
    // 主循环
    while (window.isOpen()) {
        indexs++;
        sf::Event event;// 声明一个 sf::Event 对象，用于存储窗口事件
        // 循环处理窗口事件
        while (window.pollEvent(event)) {
            sfwindowclose(window, event);  // 检查 SFML 窗口事件
            /*if (event.type == sf::Event::Resized) {
                // 更新窗口大小变量
                config.main_window_x_size = event.size.width;
                config.main_window_y_size = event.size.height;
                config.windowSize = {config.main_window_x_size, config.main_window_y_size};

                // 更新视图以适应新的窗口大小
                float aspectRatio = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);
                config.view.setSize(config.main_window_x_size * aspectRatio, config.main_window_y_size);
                window.setView(config.view);
                cout<<window.getSize().y<<" : "<<config.main_window_y_size<<endl;
            }*/
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
                // 根据滑块位置更新音频播放位置
                float sliderPercentage = (sliderHandle.getPosition().x - sliderBackground.getPosition().x) / sliderBackground.getSize().x;
                sf::Time newTime = audio.music.getDuration() * sliderPercentage;
                audio.music.setPlayingOffset(newTime);
                std::cout << "Audio playing offset set to " << newTime.asSeconds() << " seconds" << std::endl;
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
                    // float sliderPercentage = (sliderHandle.getPosition().x - sliderBackground.getPosition().x) / sliderBackground.getSize().x;
                    // sf::Time newTime = audio.music.getDuration() * sliderPercentage;
                    // audio.music.setPlayingOffset(newTime);
                    // std::cout << "Audio playing offset set to " << newTime.asSeconds() << " seconds" << std::endl;
                }
            }

            // 检查是否按下键盘
            else if (event.type == sf::Event::KeyPressed) {
                //空格键
                if(event.key.code == sf::Keyboard::Space){
                    if (audio.music.getStatus() == sf::Music::Playing) {
                        audio.music.pause();  // 暂停音频播放
                        std::cout << "Music paused" << std::endl;
                    } else if (audio.music.getStatus() != sf::Music::Playing) {
                        audio.music.play();  // 恢复音频播放
                        std::cout << "Music resumed" << std::endl;
                    }
                } else if(event.key.code == sf::Keyboard::Enter){
                    audio.music.stop();
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    audio.volume += 5.0f;
                    if (audio.volume > 100.0f) audio.volume = 100.0f;
                    audio.setVolume();
                    std::cout << "Volume: " << audio.volume << std::endl;
                } else if (event.key.code == sf::Keyboard::Down) {
                    audio.volume -= 5.0f;
                    if (audio.volume < 0.0f) audio.volume = 0.0f;
                    audio.setVolume();
                    std::cout << "Volume: " << audio.volume << std::endl;
                }
            }
        }
        // 如果鼠标没有按下，更新滑块位置以匹配音乐播放位置
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            float sliderPercentage = audio.music.getPlayingOffset().asSeconds() / audio.music.getDuration().asSeconds();
            float newX = sliderBackground.getPosition().x + sliderPercentage * sliderBackground.getSize().x - sliderHandle.getSize().x / 2;
            sliderHandle.setPosition(newX, sliderHandle.getPosition().y);
        }

        // 获取当前播放位置
        const sf::Time currentTime = audio.music.getPlayingOffset();
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
        
        // 加载图片
        sf::Texture imageTexture;
        if (!imageTexture.loadFromFile(config.cover_file)) {
            throw std::runtime_error("Failed to load image file");
        }
        sf::Sprite sprite(imageTexture);

        // 获取窗口和图片的大小
        sf::Vector2u textureSize = imageTexture.getSize();

        // 计算缩放比例
        float scaleX = static_cast<float>(config.main_window_x_size) / textureSize.x;
        float scaleY = static_cast<float>(config.main_window_x_size) / textureSize.y;

        // 设置缩放比例
        sprite.setScale(scaleX, scaleY);

        // 设置图片位置
        sprite.setPosition(0, centershape(window,{scaleX, static_cast<float>(config.windowSize.x)}).y);
        //clog<<centershape(window,{scaleX,scaleY*textureSize.y}).y<<scaleY*textureSize.y<<endl;
        int bgalphai = 255 - volumeFactor * 255;
        unsigned bgalpha = bgalphai < 1?3:bgalphai;
        bgalpha = bgalpha > 255?255:bgalpha;
        unsigned bgunalpha = volumeFactor * 255 / 2 > 255 ? 255 : volumeFactor * 255 / 2 ;
        // 根据实时音量设置透明度
        sprite.setColor(sf::Color(255, 255, 255, bgalpha));
        // 根据实时音量绘制矩形
        sf::RectangleShape rectangle(sf::Vector2f(4, 200 * volumeFactor + 20));
        rectangle.setRotation(180);
        // 设置矩形的位置，使其在窗口中居中，并将其水平位置向右移动一个矩形的宽度
        rectangle.setPosition(sfcentershape(window, rectangle).x + rectangle.getGlobalBounds().width, config.main_window_y_size + 19);
        //rectangle.setFillColor(sf::Color(255, 13, 80, bgalpha));
        rectangle.setFillColor(sf::Color(255, 13, 40, bgalpha * 2 > 255 ? 255 : bgalpha * 2));

        // 根据实时音量绘制圆形
        sf::CircleShape circle(90 * volumeFactor + config.main_window_x_size / 8 );
        circle.setPosition(sfcentershape(window,circle).x, sfcentershape(window,circle).y);// 设置圆形位置
        circle.setFillColor(sf::Color(255, 13, 80)); 
        // 绘制带有纹理的圆形
        sf::CircleShape circleHasTexture(50 * volumeFactor + config.main_window_x_size / 8);
        circleHasTexture.setPosition(sfcentershape(window,circleHasTexture).x, sfcentershape(window,circleHasTexture).y);// 设置圆形位置
        //circleHasTexture.setFillColor(sf::Color::White);
        circleHasTexture.setTexture(&imageTexture); 

        // 设置文本的大小
        text.setCharacterSize(30 * volumeFactor + 30); // 设置字符大小
        text.setFillColor(sf::Color::White); // 设置字符颜色
        text.setPosition(150 - text.getGlobalBounds().width / 2, config.main_window_y_size - 150 - text.getGlobalBounds().height / 2); // 设置文本位置

        {// 绘图
            // 绘图前先清空窗口，设置背景颜色为黑色
            window.clear(sf::Color(0, 0, 0, 0));  
            window.setView(config.view);
            // 绘制图片
            window.draw(sprite);
            // 绘制滑块
            window.draw(sliderBackground);
            window.draw(sliderHandle);

            {// 绘制矩形
                window.draw(rectangle);
                // 向右移动的距离为一个矩形的宽度加上 3 个像素
                for (int i = 2; rectangle.getPosition().x > 0 && rectangle.getPosition().x < config.main_window_x_size ; i++){
                    rectangle.setPosition(sfcentershape(window, rectangle).x + rectangle.getGlobalBounds().width * i + 1 * (i - 1) , config.main_window_y_size + rand() % 10 * volumeFactor + 19);
                    rectangle.setFillColor(sf::Color(255, 13, 0 + i * 2 > 255 ? 510 - i * 2 : i * 2, bgalpha * 2 > 255 ? 255 : bgalpha * 2));
                    window.draw(rectangle);
                }
                //bgalpha * 2 > 255 ? 255 : bgalpha * 2;
                // 恢复矩形位置
                rectangle.setPosition(sfcentershape(window, rectangle).x + rectangle.getGlobalBounds().width, config.main_window_y_size + 19);
                // 向左移动
                for (int i = 0; rectangle.getPosition().x > 0 && rectangle.getPosition().x < config.main_window_x_size ; i++){
                    rectangle.setPosition(sfcentershape(window, rectangle).x - rectangle.getGlobalBounds().width * i - 1 * (i + 1), config.main_window_y_size  + rand() % 10 * volumeFactor + 19);
                    rectangle.setFillColor(sf::Color(255, 13, 0 + i * 2 > 255 ? 510 - i * 2 : i * 2, bgalpha * 2 > 255 ? 255 : bgalpha * 2));
                    window.draw(rectangle);
                }
            }
            window.draw(circle);
            window.draw(circleHasTexture);
            window.draw(text);
            window.display();  // 显示绘制的内容
        }
        // 震动
        if(audio.music.getStatus() == sf::Music::Playing && config.shake_effect){
            config.view.setCenter(config.main_window_x_size / 2 + (rand() % 20 - 10) * volumeFactor, config.main_window_y_size / 2 + (rand() % 20 - 10) * volumeFactor);
        }
    }

    return 0;
} 