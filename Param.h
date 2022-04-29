// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/27
// Description: 参数类
#ifndef GRAPHLAYOUT_PARAM_H
#define GRAPHLAYOUT_PARAM_H

#include <cmath>

class Param {
    double epsilon_;
    double delta_;
    double gamma_;
public:
    static constexpr double TWOPI = 2 * M_PI;
    static constexpr double ONE = 1.0;

    virtual ~Param();

    Param() = default;
    Param(double epsilon, double delta, double gamma);

    double getEpsilon() const;

    void setEpsilon(double epsilon);

    double getDelta() const;

    void setDelta(double delta);

    double getGamma() const;

    void setGamma(double gamma);
};


#endif //GRAPHLAYOUT_PARAM_H
