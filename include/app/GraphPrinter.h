#pragma once
#include <string>
#include "ui/UserInterface.h"
#include "structures/Matrix.h"
#include "structures/ListsOfNeighbors.h"

namespace SDIZO {
    class GraphPrinter {
    private:
        UserInterface* ui = nullptr;
    public:
        /**
         * @brief Construct a new Graph Printer object
         * 
         * @param ui 
         */
        GraphPrinter(UserInterface* i);

        /**
         * @brief Print graph in form of matrix
         * 
         * @param m 
         */
        void printMatrix(Matrix<int>* matrix);

        /**
         * @brief Print graph in form of lists of neighbors
         * 
         * @param l 
         */
        void printList(ListsOfNeighbors* l);
    };
};