#include "GraphLayout.h"
#include "KCoreLayout.h"
#include <iostream>

int main() {
    GraphLayout graphLayout;

    KCoreLayout kCoreLayout;

    //auto initLayout = graphLayout.getLayout();
    graphLayout.setLayout([&](Graph &G, GraphAttributes &GA) {
        //initLayout(G, GA);
        kCoreLayout.call(GA);
    });

    graphLayout();
    return 0;
}
