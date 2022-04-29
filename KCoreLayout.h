// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/25
// Description: 
#ifndef GRAPHLAYOUT_KCORELAYOUT_H
#define GRAPHLAYOUT_KCORELAYOUT_H

#include "Vertex.h"
#include "Component.h"
#include "Shell.h"
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <vector>
#include <cmath>

using namespace ogdf;

class KCoreLayout : public std::enable_shared_from_this<KCoreLayout>{
    std::vector<Vertex> vertexs_;
    int V_;
    std::vector<std::vector<int>> adjList_;
    std::vector<std::shared_ptr<Component>> componets_;
    int E_;
    std::vector<std::vector<int>> shells_;
    int c_max_;


    void initGraph(const Graph& G); //初始化图：点、边
    void kCoreDecomposition();      //k核分解得到k壳
    void partition();               //将k壳划分为组件、壳、簇
    void layout();                  //对每个组件中的节点进行布局
    void draw(GraphAttributes &GA); //将坐标信息返回

public:
    virtual ~KCoreLayout();
    KCoreLayout();
    std::vector<std::unordered_set<int>> calForConnected(const std::unordered_set<int> &nodes) const;
    std::vector<Vertex> &getVertexs();
    void call(GraphAttributes &GA);
};



#endif //GRAPHLAYOUT_KCORELAYOUT_H
