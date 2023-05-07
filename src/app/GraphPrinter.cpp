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
    
}