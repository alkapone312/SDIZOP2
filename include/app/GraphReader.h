#pragma once
#include "exception/Exception.h"
#include "utils/FileReader.h"
#include "structures/Matrix.h"
#include "structures/ListsOfNeighbors.h"
#include "app/GraphInfo.h"

namespace SDIZO {
    class GraphReader {
    private:
        FileReader* reader = nullptr;
        bool directed = true;
    public:
        /**
         * @brief Set the Reader object
         * 
         * @param r 
         */
        GraphReader(FileReader* r, bool directed);

        /**
         * @brief Read graph from file to matrix structure
         * 
         * @return Matrix<int> 
         */
        Matrix<int> readMatrix();

        /**
         * @brief Read graph from file to list structure
         * 
         * @return ListsOfNeighbors 
         */
        ListsOfNeighbors readList();

        /**
         * @brief Get the Graph Info object
         * 
         * @return GraphInfo 
         */
        GraphInfo getGraphInfo();

    private:
        /**
         * @brief Get the Edge Info object
         * 
         * @return EdgeInfo 
         */
        EdgeInfo getEdgeInfo();
    };
};