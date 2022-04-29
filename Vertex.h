// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/25
// Description: 
#ifndef GRAPHLAYOUT_VERTEX_H
#define GRAPHLAYOUT_VERTEX_H

#include "Param.h"
#include "Singleton.h"
#include "Component.h"
#include <ogdf/basic/Graph.h>
#include <memory>

class Component;

class Vertex {
    double x_, y_, rho_, alpha_, rho_a_, rho_b_, a_, b_;
    ogdf::node node_;
    int c_;
    std::weak_ptr<Component> component_;
public:
    ogdf::node getNode() const {
        return node_;
    }

    void setCdr() {
        double epsilon = SingleTon<Param>::getInstance()->getEpsilon();
        setRho((1 - epsilon) * getRhoA() + epsilon * getRhoB());
        double gamma = SingleTon<Param>::getInstance()->getGamma();
        auto component = component_.lock();
        setX(component->getX() + gamma * getA() * getRho());
        setY(component->getY() + gamma * getB() * getRho());
    }

    void setRandom() {
        double gamma = SingleTon<Param>::getInstance()->getGamma();
        auto component = component_.lock();
        setRho(utils::Random<double>::get(1.0));
        setX(component->getX() + gamma * getA() * getRho());
        setY(component->getY() + gamma * getB() * getRho());
    }

    double getRhoA() const {
        return rho_a_;
    }

    void setRhoA(double rhoA) {
        rho_a_ = rhoA;
    }

    double getRhoB() const {
        return rho_b_;
    }

    void setRhoB(double rhoB) {
        rho_b_ = rhoB;
    }

    double getA() const {
        return a_;
    }

    void setA(double a) {
        a_ = a;
    }

    double getB() const {
        return b_;
    }

    void setB(double b) {
        b_ = b;
    }

    const std::weak_ptr<Component> &getComponent() const {
        return component_;
    }

    void setComponent(const std::weak_ptr<Component> &component) {
        component_ = component;
    }

    double getX() const {
        return x_;
    }

    void setX(double x) {
        x_ = x;
    }

    double getY() const {
        return y_;
    }

    void setY(double y) {
        y_ = y;
    }

    double getRho() const {
        return rho_;
    }

    void setRho(double rho) {
        rho_ = rho;
    }

    double getAlpha() const {
        return alpha_;
    }

    void setAlpha(double alpha) {
        alpha_ = alpha;
    }

    int getC() const {
        return c_;
    }

    void setC(int c) {
        c_ = c;
    }

public:
    explicit Vertex(const ogdf::node node)
        : node_(node) {

    }
};


#endif //GRAPHLAYOUT_VERTEX_H
