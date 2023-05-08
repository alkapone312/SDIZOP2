#include "app/GraphPrinter.h"

using namespace SDIZO;

GraphPrinter::GraphPrinter(UserInterface* i) {
    ui = i;
}

void GraphPrinter::printMatrix(Matrix<int> matrix) {
    for (int i = 0; i < matrix.getRows(); ++i) {
        std::string line = "    ";
        for (int j = 0; j < matrix.getCols(); ++j) {
            int weight = matrix(i, j);
            std::string weightString = weight == INT32_MAX ? "oo" : std::to_string(weight);
            line += weightString + "    ";
        }
        ui->info(line);
    }
}

void GraphPrinter::printList(ListsOfNeighbors l) {
    for(int i = 0; i < l.getNumberOfVertices(); i++) {
        std::string listOfNeighbors = std::to_string(i) + ": ";
        for(int j = 0; j < l.getNumberOfNeighbors(i); j++) {
            if(j != 0) listOfNeighbors += ", ";
            Vector2 edge = l.getEdge(i, j);
            listOfNeighbors += "( " + std::to_string(edge.x) + ", " + std::to_string(edge.y) + " )";
        }
        ui->info(listOfNeighbors);
    }
}