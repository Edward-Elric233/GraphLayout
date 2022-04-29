// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/27
// Description: 
#include "Param.h"

constexpr double Param::TWOPI;
constexpr double Param::ONE;

double Param::getEpsilon() const {
    return epsilon_;
}

void Param::setEpsilon(double epsilon) {
    epsilon_ = epsilon;
}

double Param::getDelta() const {
    return delta_;
}

void Param::setDelta(double delta) {
    delta_ = delta;
}

double Param::getGamma() const {
    return gamma_;
}

void Param::setGamma(double gamma) {
    gamma_ = gamma;
}

Param::Param(double epsilon, double delta, double gamma) : epsilon_(epsilon), delta_(delta), gamma_(gamma) {}

Param::~Param() {

}
