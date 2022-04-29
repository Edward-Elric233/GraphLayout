// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/27
// Description: 使用C++11实现的线程安全的单例对象
#ifndef GRAPHLAYOUT_SINGLETON_H
#define GRAPHLAYOUT_SINGLETON_H

#include "utils.h"
#include <memory>
#include <mutex>
#include <thread>

template<typename T>
class SingleTon {
    using Ptr = std::shared_ptr<T>;
    static Ptr p;
    static std::once_flag flag;
public:
    template<typename ...Args>
    static Ptr getInstance(Args&& ...args) {
        auto init = [](auto&&... args1) {
            std::thread t([]{});
            t.join();   //为了引入pthread_create
            //TODO:会对参数进行拷贝，如何给可调用对象传递参数包？
            p.reset(new T(std::move(args1)...));
        };
        std::call_once(flag, init, std::forward<Args>(args)...);
        return p;
    }
};

template<typename T>
typename SingleTon<T>::Ptr SingleTon<T>::p;

template<typename T>
std::once_flag SingleTon<T>::flag;

#endif //GRAPHLAYOUT_SINGLETON_H
