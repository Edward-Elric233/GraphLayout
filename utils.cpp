// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/28
// Description: 

#include "utils.h"

namespace utils {

    double Random<double>::last_max = 1, Random<double>::last_min = 0;
    std::default_random_engine Random<double>::e(std::chrono::system_clock::now().time_since_epoch().count()); //初始化随机数种子
    std::uniform_real_distribution<> Random<double>::u(last_min, last_max);
    double Random<double>::get(double max_, double min_) {
        if (max_ <= min_) return 0;
        constexpr double EPS = 1e-8;    //无穷小量
        if (last_max != max_ || last_min != min_) {
            last_max = max_;
            last_min = min_;
            u.param(decltype(u)::param_type{min_, max_ - EPS});
        }
        return u(e);
    }
}

namespace std {
    hash<long long> hash<pair<int, int>>::helper;
}