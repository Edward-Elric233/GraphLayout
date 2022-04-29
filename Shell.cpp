// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/27
// Description: 
#include "Shell.h"
#include "KCoreLayout.h"
#include "utils.h"
#include "Param.h"

Shell::Shell(const std::weak_ptr<Component> &component): component_(component) {}

Shell::~Shell() {

}

std::unordered_set<int> &Shell::getNodes() {
    return nodes_;
}

const std::weak_ptr<Component> &Shell::getComponent() const {
    return component_;
}

void Shell::layout(const std::shared_ptr<KCoreLayout> &kCoreLayout) {
    auto clusters_nodes = kCoreLayout->calForConnected(nodes_);
    auto &vertexs = kCoreLayout->getVertexs();
    double alpha = 0, frac;
    for (auto &cluster_nodes : clusters_nodes) {
        frac = static_cast<double>(cluster_nodes.size()) / nodes_.size();
        utils::Normal normal(frac / 2, M_PI * frac);
        for (auto u : cluster_nodes) {
            vertexs[u].setAlpha(alpha + normal());
        }
        alpha += frac * Param::TWOPI;
    }
}