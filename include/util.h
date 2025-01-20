#pragma once
#include "commonheaders.h"
//namespace util{
// 函数 sfwindowcenter：计算窗口中心点的坐标
// @param window: 要计算中心点的 sf::RenderWindow 对象
// @return sf::Vector2u: 包含窗口中心点坐标的 sf::Vector2u 对象
sf::Vector2u sfwindowcenter(sf::RenderWindow& window) {
    // 获取窗口大小
    sf::Vector2u windowSize = window.getSize();
    // 计算窗口中心点坐标
    sf::Vector2u center(windowSize.x / 2, windowSize.y / 2);
    // 返回窗口中心点坐标
    return center;
}

// 函数 windowcenter：计算给定大小窗口中心点的坐标
// 参数：
//   - window_x_size: 窗口的宽度
//   - window_y_size: 窗口的高度
// 返回值：
//   - sf::Vector2u: 包含窗口中心点坐标的 sf::Vector2u 对象
sf::Vector2u windowcenter(unsigned int window_x_size, unsigned int window_y_size) {
    // 计算窗口中心点坐标
    sf::Vector2u center(window_x_size / 2, window_y_size / 2);
    // 返回窗口中心点坐标
    return center;
}

// 函数 sfcentershape：计算形状在窗口中心点时的位置
// 参数：
//   - window: sf::RenderWindow 对象
//   - shape: sf::Shape 对象
// 返回值：
//   - sf::Vector2f: 包含形状在窗口中心点时的位置坐标的 sf::Vector2f 对象
sf::Vector2f sfcentershape(sf::RenderWindow& window, sf::Shape& shape) {
    // 获取窗口大小
    sf::Vector2u windowSize = window.getSize();
    // 获取形状的全局边界框
    sf::FloatRect shapeBounds = shape.getGlobalBounds();
    // 计算形状在窗口中心点时的位置
    sf::Vector2f center(windowSize.x / 2 - shapeBounds.width / 2, windowSize.y / 2 - shapeBounds.height / 2);
    // 返回形状在窗口中心点时的位置
    return center;
}

// 函数 sfcentershape：计算形状在窗口中心点时的位置
// 参数：
//   - window: sf::RenderWindow 对象
//   - 
// 返回值：
//   - sf::Vector2f: 包含形状在窗口中心点时的位置坐标的 sf::Vector2f 对象
sf::Vector2f centershape(sf::RenderWindow& window, const sf::Vector2f& shapexy) {
    // 获取窗口大小
    sf::Vector2u windowSize = window.getSize();
    // 计算形状在窗口中心点时的位置
    sf::Vector2f center(windowSize.x / 2 - shapexy.x / 2, windowSize.y / 2 - shapexy.y / 2);
    // 返回形状在窗口中心点时的位置
    return center;
}

// 函数 sfcentershape：计算形状在窗口中心点时的位置
// 参数：
//   - window: sf::RenderWindow 对象
//   - 
// 返回值：
//   - sf::Vector2f: 包含形状在窗口中心点时的位置坐标的 sf::Vector2f 对象
sf::Vector2f centershapeu(sf::RenderWindow& window, sf::Vector2u& shapexyu) {
    // 获取窗口大小
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f shapexy({static_cast<float>(shapexyu.x),static_cast<float>(shapexyu.y)});
    // 计算形状在窗口中心点时的位置
    sf::Vector2f center(windowSize.x / 2 - shapexy.x / 2, windowSize.y / 2 - shapexy.y / 2);
    // 返回形状在窗口中心点时的位置
    return center;
}

// 函数 sfwindowclose：检查并关闭 SFML 窗口
//
// @param window: 要检查和关闭的 sf::RenderWindow 对象
// @param event: 用于存储窗口事件的 sf::Event 对象
void sfwindowclose(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        // 关闭窗口
        window.close();
    }
}