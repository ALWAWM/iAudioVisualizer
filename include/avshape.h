#pragma once
#include "commonheaders.h"
template <typename T>
class AVShape {
private:
    T* shape;
public:
    AVShape(T* shape);

    // 获取形状的引用
    T& getShape() {
        return shape;
    }

    //...
};