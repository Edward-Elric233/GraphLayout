// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/27
// Description: 
#include "Component.h"
#include "Shell.h"
#include "utils.h"
#include "KCoreLayout.h"

Component::Component(): x_(0), y_(0), u_(1), c_(0) {}   //初始化的Component，x,y,c=0,u=1
Component::~Component() {

}

double Component::getX() const {
    return x_;
}

void Component::setX(double x) {
    x_ = x;
}

double Component::getY() const {
    return y_;
}

void Component::setY(double y) {
    y_ = y;
}

double Component::getU() const {
    return u_;
}

void Component::setU(double u) {
    u_ = u;
}

double Component::getA() const {
    return a_;
}

void Component::setA(double a) {
    a_ = a;
}

double Component::getB() const {
    return b_;
}

void Component::setB(double b) {
    b_ = b;
}

double Component::getRho() const {
    return rho_;
}

void Component::setRho(double rho) {
    rho_ = rho;
}

double Component::getPhi() const {
    return phi_;
}

void Component::setPhi(double phi) {
    phi_ = phi;
}

const std::weak_ptr<Component> &Component::getParent() const {
    return parent_;
}

void Component::setParent(const std::weak_ptr<Component> &parent) {
    parent_ = parent;
}

std::unordered_set<int> &Component::getNodes() {
    return nodes_;
}

int Component::getC() const {
    return c_;
}

void Component::setC(int c) {
    c_ = c;
}

std::shared_ptr<Shell> Component::addShell() {
    shells_.emplace_back(std::make_shared<Shell>(shared_from_this()));
    return shells_.back();
}

/*
std::ostream &operator<<(std::ostream &os, const Component &component) {
    return os;
}
 */

void Component::layout(const std::shared_ptr<KCoreLayout> &kCoreLayout) {
    for (auto &shell : shells_) {
        shell->layout(kCoreLayout);
    }
}

void Component::setCdr() {
    auto parent = parent_.lock();
    double delta = SingleTon<Param>::getInstance()->getDelta();
    setX(parent->getX() + delta * getA());
    setY(parent->getY() + delta * getB());
}