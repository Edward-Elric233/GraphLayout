// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/27
// Description: 使用C++11实现的线程安全的单例对象
#ifndef GRAPHLAYOUT_SINGLETON_H
#define GRAPHLAYOUT_SINGLETON_H

#include <memory>
#include <mutex>

template<typename T>
class SingleTon {
    using Ptr = std::shared_ptr<T>;
    //static Ptr p;
    static std::once_flag flag;
public:
    template<typename ...Args>
    static Ptr getInstance(Args&& ...args) {
        /*
        auto init = [](Ptr &p, auto&& ...args1) {
            p.reset(new T(std::forward<decltype(args1)>(args1)...));
        };
        std::call_once(flag, init, p, std::forward<Args>(args)...);
         */
        static Ptr p = std::make_shared<T>(std::forward<Args>(args)...);
        return p;
    }
};

/*
template<typename T>
std::shared_ptr<T> SingleTon<T>::p;
 */

template<typename T>
std::once_flag SingleTon<T>::flag;

#endif //GRAPHLAYOUT_SINGLETON_H
