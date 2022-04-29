// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/25
// Description: 
#include "KCoreLayout.h"
#include "utils.h"
#include "Param.h"
#include "Singleton.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <list>
#include <functional>

std::vector<std::unordered_set<int>> KCoreLayout::calForConnected(const std::unordered_set<int> &nodes) const {
    std::unordered_set<int> vis;
    std::vector<std::unordered_set<int>> components;    //连通分量

    std::function<void(int, std::unordered_set<int> &)> dfs; //递归访问连通分量
    dfs = [&](int u, std::unordered_set<int> &component) {
        component.insert(u);
        vis.insert(u);

        for (auto v : adjList_[u]) {
            if (nodes.count(v) && !vis.count(v)) {
                dfs(v , component);
            }
        }
    };

    for (auto u : nodes) {
        if (vis.count(u)) continue; //已经访问过u了

        components.emplace_back();
        dfs(u, components.back());
    }

    return components;
}

void KCoreLayout::initGraph(const Graph &G) {
    V_ = G.nodes.size();
    E_ = G.edges.size();

    std::unordered_map<ogdf::node, int> mp;
    int t = 0;
    for (auto node : G.nodes) {
        vertexs_.emplace_back(node);
        mp[node] = t++;
    }

    adjList_.resize(V_);

    int u, v;
    std::unordered_set<std::pair<int, int>> edge_set;   //手动去重
    for (auto edge : G.edges) {
        u = mp[edge->source()];
        v = mp[edge->target()];
        if (u > v) std::swap(u, v);
        if (u == v || edge_set.count(std::make_pair(u, v))) continue;   //如果出现自环或者重边则跳过
        edge_set.emplace(u, v);
        //无向图
        adjList_[u].push_back(v); adjList_[v].push_back(u);
    }

    /*
    //debug
    utils::print("node number:", V_, "edge number", E_);
    for (int i = 0; i < V_; ++i) {
        auto &adjList = adjList_[i];
        std::cout << i << " : ";
        utils::printArr(adjList);
    }
     */
}

void KCoreLayout::kCoreDecomposition() {
    std::vector<int> degree(V_);
    int maxDegree = 0;

    for (int i = 0; i < V_; ++i) {
        degree[i] = adjList_[i].size();
        maxDegree = std::max(maxDegree, degree[i]);
    }

    std::vector<std::vector<int>> buckets(maxDegree + 1);
    for (int i = 0; i < V_; ++i) buckets[degree[i]].push_back(i);

    std::vector<bool> vis(V_, false);   //记录节点是否处理过
    int cnt = 0;        //记录已经处理过的节点的个数

    //处理度为0的节点
    shells_.emplace_back();
    for (auto x : buckets[0]) {
        shells_[0].push_back(x);
        vis[x] = true;
        ++cnt;
    }

    int k, u;
    for (k = 1; k <= maxDegree; ++k) {
        if (cnt == V_) break;   //已经没有节点可处理
        shells_.emplace_back();
        auto &shell = shells_.back();
        auto &bucket = buckets[k];

        for (int i = 0; i < bucket.size(); ++i) {   //只能用下标索引，因为还会在后面添加节点
            u = bucket[i];
            if (vis[u]) continue;   //已经处理过这个节点了

            shell.push_back(u);
            vertexs_[u].setC(k);
            vis[u] = true;
            ++cnt;

            for (auto v : adjList_[u]) {
                if (degree[v] > k) {
                    buckets[--degree[v]].push_back(v);
                }
            }
        }
    }

    c_max_ = shells_.size() - 1;

    /*
    //debug
    for (int i = 0; i < k; ++i) {
        auto &shell = shells_[i];
        std::cout << i << " : ";
        utils::printArr(shell);
    }
     */
}

void KCoreLayout::partition() {
    std::list<std::weak_ptr<Component>> components_list;    //用链表存储需要处理的组件

    //初始化，添加第一个组件
    {
        componets_.emplace_back(std::make_shared<Component>());
        auto &component = componets_.back();
        auto &nodes = component->getNodes();
        for (int i = 0; i < V_; ++i) nodes.insert(i);
        components_list.push_back(component);
    }

    int n;

    while ((n = components_list.size()) > 0) {
        //循环处理component
        auto iter = components_list.begin();
        while (n--) {
            auto component = iter->lock();
            auto &component_nodes = component->getNodes();

            auto shell = component->addShell();
            auto &shell_nodes = shell->getNodes();

            int c = component->getC();
            for (auto u : shells_[c]) {
                if (component_nodes.count(u)) {
                    shell_nodes.insert(u);
                    vertexs_[u].setComponent(component);
                    component_nodes.erase(u);
                }
            }

            /*
             * 计算剩下的component
             */
            ++c;    //core的shell index
            //1.计算连通分量
            auto new_components_nodes = calForConnected(component_nodes);
            //2.生成新component
            if (new_components_nodes.size() == 0) {
                iter = components_list.erase(iter);
            } else if (new_components_nodes.size() == 1) {
                //只有一个连通分量
                component->setC(c);
            } else {
                //多个连通分量
                iter = components_list.erase(iter);
                double phi_init = utils::Random<double>::get(Param::TWOPI);
                int sum_sz = 0;
                double rate, t;
                for (auto &new_component_nodes : new_components_nodes) {
                    componets_.emplace_back(std::make_shared<Component>());
                    auto &new_component = componets_.back();

                    //对新的连通分量进行初始化
                    new_component->setC(c);
                    new_component->setParent(component);

                    rate = static_cast<double>(new_component_nodes.size()) / component_nodes.size();
                    new_component->setU(component->getU() * rate);
                    new_component->setRho(Param::ONE - rate);
                    phi_init += Param::TWOPI * rate;
                    new_component->setPhi(phi_init);

                    t = (c_max_ - c) * new_component->getU() * new_component->getRho();
                    new_component->setA(t * std::cos(new_component->getPhi()));
                    new_component->setB(t * std::sin(new_component->getPhi()));

                    new_component->setCdr();

                    //TODO:这里使用move应该不会有什么问题
                    new_component->getNodes() = std::move(new_component_nodes);
                    //将new_component放入需要处理的组件中
                    components_list.push_back(new_component);
                }
            }
        }

    }

}

void KCoreLayout::layout() {
    for (auto &component : componets_) {
        //cal alpha
        component->layout(shared_from_this());
    }
    for (int u = 0; u < V_; ++u) {
        auto &vertex = vertexs_[u];
        int c = vertex.getC();
        vertex.setRhoA(c_max_ - c);

        int cnt = 0, sum = 0, t;
        for (auto v : adjList_[u]) {
            t = vertexs_[v].getC();
            if (t >= c) {
                ++cnt;
                sum += c_max_ - t;
            }
        }
        vertex.setRhoB(static_cast<double>(sum) / cnt);

        double unit = vertex.getComponent().lock()->getU();
        vertex.setA(unit * std::cos(vertex.getAlpha()));
        vertex.setB(unit * std::sin(vertex.getAlpha()));

        vertex.setCdr();
    }
}

void KCoreLayout::draw(GraphAttributes &GA) {
    for (int i = 0; i < V_; ++i) {
        auto &vertex = vertexs_[i];
        GA.x(vertex.getNode()) = vertex.getX();
        GA.y(vertex.getNode()) = vertex.getY();
    }
}

void KCoreLayout::call(GraphAttributes &GA) {
    initGraph(GA.constGraph());
    kCoreDecomposition();
    partition();
    layout();
    draw(GA);
}

KCoreLayout::KCoreLayout() {
    //初始化参数
    SingleTon<Param>::getInstance(0.5, 100, 100);
}

KCoreLayout::~KCoreLayout() {}

std::vector<Vertex> &KCoreLayout::getVertexs() {
    return vertexs_;
}
