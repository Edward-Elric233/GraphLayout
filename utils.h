// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/25
// Description: 工具类和工具函数
#ifndef GRAPHLAYOUT_UTILS_H
#define GRAPHLAYOUT_UTILS_H

#include <iostream>
#include <unordered_set>
#include <climits>
#include <random>
#include <chrono>

namespace utils {
    inline void print() {
        std::cout << std::endl;
    }
    template<typename T, typename ...Args>
    void print(T &&t, Args &&...args) {
        std::cout << t << " ";
        print(std::forward<Args>(args)...);
    }

    template<typename Container>
    void printArr(Container &&arr) {
        for (auto x : arr) {
            std::cout << x << " ";
        }
        print();
    }

    template<typename T>
    class Random;

    template<>
    class Random<double> {
        static std::default_random_engine e;
        static double last_max, last_min;
        static std::uniform_real_distribution<> u;
    public:
        static double get(double max_ = INT_MAX, double min_ = 0);
    };

    class Normal {
        std::default_random_engine e;
        std::normal_distribution<> n;
    public:
        explicit Normal(double mu = 0, double sigma = 1)
            : e(std::chrono::system_clock::now().time_since_epoch().count())
            , n(mu, sigma) {

        }
        ~Normal() {

        }
        double operator() () {
            return n(e);
        }
    };

}

namespace std {
    template<>
    struct hash<pair<int, int>> {
        using argument_type = pair<int, int>;
        using result_type = size_t;
        static hash<long long> helper;
        result_type operator() (const argument_type& pr) const {
            return static_cast<long long>(pr.first) * INT_MAX + pr.second;
        }
    };

}

#endif //GRAPHLAYOUT_UTILS_H
