#include "app/GraphReader.h"

using namespace SDIZO;

GraphReader::GraphReader(FileReader* r, bool directed) {
    reader = r;
    this->directed = directed;
}

Matrix<int> GraphReader::readMatrix() {
    if(reader == nullptr) {
        throw new Exception("Reader not defined!");
    }

    GraphInfo gi = getGraphInfo();
    Matrix<int> m = Matrix<int>::create(gi.vertexQuantity, gi.vertexQuantity, [](int row, int col) -> int {
        return INT32_MAX;
    });

    for(int i = 0; i < gi.edgeQuantity; i++) {
        if(!reader->isData()) {
            throw new Exception("File corrupted");
        }
        EdgeInfo ei = getEdgeInfo();
        m.set(ei.startingVertex, ei.endingVertex, ei.weight);
        if(!directed) {
            m.set(ei.endingVertex, ei.startingVertex, ei.weight);
        }
    }

    return m;
}

ListsOfNeighbors GraphReader::readList() {
    if(reader == nullptr) {
        throw new Exception("Reader not defined!");
    }

    GraphInfo gi = getGraphInfo();

    ListsOfNeighbors l(gi.vertexQuantity);

    for(int i = 0; i < gi.edgeQuantity; i++) {
        if(!reader->isData()) {
            throw new Exception("File corrupted");
        }
        EdgeInfo ei = getEdgeInfo();
        l.addEdge(ei.startingVertex, ei.endingVertex, ei.weight);
        if(!directed) {
            l.addEdge(ei.endingVertex, ei.startingVertex, ei.weight);
        }
    }

    return l;
}

GraphInfo GraphReader::getGraphInfo() {
    GraphInfo gi;
    reader->reset();
    gi.edgeQuantity = reader->getData();
    gi.vertexQuantity = reader->getData();
    gi.startingVertex = reader->getData();
    gi.endingVertex = reader->getData();

    return gi;
}

EdgeInfo GraphReader::getEdgeInfo() {
    EdgeInfo ei;
    ei.startingVertex = reader->getData();
    ei.endingVertex = reader->getData();
    ei.weight = reader->getData();

    return ei;
}