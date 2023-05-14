#pragma once
namespace SDIZO {
    struct GraphInfo {
        int edgeQuantity;
        int vertexQuantity;
        unsigned int startingVertex;
        unsigned int endingVertex;
    };

    struct EdgeInfo {
        unsigned int startingVertex;
        unsigned int endingVertex;
        int weight;
    };
}