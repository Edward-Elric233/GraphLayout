// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/27
// Description: 使用C++11实现的线程安全的单例对象
#ifndef GRAPHLAYOUT_SINGLETON_H
#define GRAPHLAYOUT_SINGLETON_H

#include "utils.h"
#include <memory>

template<typename T>
class SingleTon {
    using Ptr = std::shared_ptr<T>;
public:
    template<typename ...Args>
    static Ptr getInstance(Args&& ...args) {
        static Ptr p = std::make_shared<T>(std::forward<Args>(args)...);    //对于静态变量的初始化只会进行一次
        return p;
    }
};

#endif //GRAPHLAYOUT_SINGLETON_H
