// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/27
// Description: 
#ifndef GRAPHLAYOUT_SHELL_H
#define GRAPHLAYOUT_SHELL_H

#include "Component.h"
#include <memory>
#include <unordered_set>

class KCoreLayout;

class Shell {
    std::weak_ptr<Component> component_;
    std::unordered_set<int> nodes_;
public:
    std::unordered_set<int> &getNodes();
    const std::weak_ptr<Component> &getComponent() const;
    explicit Shell(const std::weak_ptr<Component> &component);
    virtual ~Shell();
    void layout(const std::shared_ptr<KCoreLayout> &kCoreLayout);
};


#endif //GRAPHLAYOUT_SHELL_H
