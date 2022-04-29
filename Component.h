// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/27
// Description: 
#ifndef GRAPHLAYOUT_COMPONENT_H
#define GRAPHLAYOUT_COMPONENT_H

#include <memory>
#include <unordered_set>
#include <vector>

class Shell;
class KCoreLayout;

class Component : public std::enable_shared_from_this<Component>{
    double x_, y_, u_, a_, b_, rho_, phi_;  //a = (c_max - c_h) * u * rho * cos(phi)
    int c_;
    std::unordered_set<int> nodes_;
    std::weak_ptr<Component> parent_;     //父亲组件好像没有什么用
    std::vector<std::shared_ptr<Shell>> shells_;

public:
    void setCdr();
    std::shared_ptr<Shell> addShell();
    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(double y);
    double getU() const;
    void setU(double u);
    double getA() const;
    void setA(double a);
    double getB() const;
    void setB(double b);
    double getRho() const;
    void setRho(double rho);
    double getPhi() const;
    void setPhi(double phi);
    const std::weak_ptr<Component> &getParent() const;
    void setParent(const std::weak_ptr<Component> &parent);
    std::unordered_set<int> &getNodes();
    int getC() const;
    void setC(int c);
    Component();
    virtual ~Component();
    //friend std::ostream& operator<< (std::ostream &os, const Component &component);   //debug
    void layout(const std::shared_ptr<KCoreLayout> &kCoreLayout);   //对Shells进行布局

};


#endif //GRAPHLAYOUT_COMPONENT_H
