// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2022/4/25
// Description: 
#include "GraphLayout.h"
#include <ogdf/basic/graph_generators.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/energybased/FMMMLayout.h>

void input(Graph& G, GraphAttributes& GA) {
    using namespace ogdf;
    randomGraph(G, 10000, 20000);

    /*
    if (!GraphIO::read(GA, G, "output.gml", GraphIO::readGML)) {
        std::cerr << "can't find file" << std::endl;
        exit(0);
    }
     */

    for (auto node : G.nodes) {
        GA.height(node) = 10;
        GA.width(node) = 10;
        GA.shape(node) = Shape::Ellipse;
        //GA.label(node) = to_string(node->index());
    }
    for (auto edge : G.edges) {
        GA.arrowType(edge) =  EdgeArrow::None;
        GA.strokeColor(edge) = Color::Name::Grey;
        GA.strokeWidth(edge) = 0.8;
    }
}

void output(const Graph& G, const GraphAttributes& GA) {
    using namespace ogdf;
    GraphIO::write(GA, "output_std.gml", GraphIO::writeGML);
    GraphIO::write(GA, "output_std.svg", GraphIO::drawSVG);
}

void layout(Graph& G, GraphAttributes& GA) {

    FMMMLayout fmmm;

    //recommended
    fmmm.useHighLevelOptions(true);
    /*
     * We then set the unit edge length (a scaling factor if you will), enable initial replacing of nodes and choose one of the available options from ogdf::FMMMOptions::QualityVsSpeed to tune tradeoffs between speed and aesthetic of the resulting graph. The only remaining high-level option is ogdf::FMMMOptions::PageFormatType which defaults to a Square if not explicitly set. These high-level options will then be used to derive the low-level settings accordingly.
     */
    fmmm.unitEdgeLength(50);
    fmmm.newInitialPlacement(true);
    fmmm.qualityVersusSpeed(FMMMOptions::QualityVsSpeed::GorgeousAndEfficient);

    fmmm.call(GA);
}

GraphLayout::GraphLayout()
    : G_()
    , GA_(G_, GraphAttributes::nodeGraphics |
              GraphAttributes::edgeGraphics |
              GraphAttributes::nodeLabel |
              GraphAttributes::nodeStyle |
              GraphAttributes::edgeType |
              GraphAttributes::edgeArrow |
              GraphAttributes::edgeStyle )
    , input_(input)
    , output_(output)
    , layout_(layout) {

}

GraphLayout::~GraphLayout() {

}