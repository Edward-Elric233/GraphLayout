#include "GraphLayout.h"
#include "KCoreLayout.h"
#include <iostream>
#include <thread>

int main() {
    GraphLayout graphLayout;

    std::shared_ptr<KCoreLayout> kCoreLayout = std::make_shared<KCoreLayout>();     //为了使用shared_from_this

    //auto initLayout = graphLayout.getLayout();
    graphLayout.setLayout([&](Graph &G, GraphAttributes &GA) {
        //initLayout(G, GA);
        kCoreLayout->call(GA);
    });

    graphLayout();
    return 0;
}
