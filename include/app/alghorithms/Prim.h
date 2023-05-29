#pragma once
#include <string>
#include "exception/Exception.h"
#include "structures/Matrix.h"
#include "structures/ListsOfNeighbors.h"
#include "structures/DoubleSidedList.h"
#include "app/alghorithms/AlghorithmResult.h"

namespace SDIZO {
    class Prim {
    private:
    public:
        Prim() {}

        AlghorithmResult* solve(Matrix<int>* m) {
            if(m->getRows() != m->getCols()) {
                throw new Exception("Unable to solve, wrong matrix");
            }

            AlghorithmResult* r = new AlghorithmResult();
            r->addToResult("Edge    Weight");

            r->startTime();
            DoubleSidedList<int>* visited = new DoubleSidedList<int>;
            visited->pushBack(0); //start from 0 vertex
            // until tree is not complete
            int count = 1;
            while(count < m->getRows()) {
                Vector3 minEdge = findMinEdge(visited, m);
                visited->pushBack(minEdge.y);
                count++;
                r->addToResult("(" + std::to_string(minEdge.x) + ", " + std::to_string(minEdge.y) + ") " + std::to_string(minEdge.z));
                r->addToMSTSum(minEdge.z);
            }
            r->stopTime();
            delete visited;

            return r;
        }

        AlghorithmResult* solve(ListsOfNeighbors* l) {
            AlghorithmResult* r = new AlghorithmResult();
            r->addToResult("Edge    Weight");

            r->startTime();
            DoubleSidedList<int>* visited = new DoubleSidedList<int>;
            visited->pushBack(0);

            int count = 1;
            while(count < l->getNumberOfVertices()) {
                Vector3 minEdge = findMinEdge(visited, l);
                visited->pushBack(minEdge.y);
                count++;
                r->addToResult("(" + std::to_string(minEdge.x) + ", " + std::to_string(minEdge.y) + ") " + std::to_string(minEdge.z));
                r->addToMSTSum(minEdge.z);
            }   
            r->stopTime();
            delete visited;

            return r;    
        }

    private:
        Vector3 findMinEdge(DoubleSidedList<int>* visited, Matrix<int>* m) {
            int min = INT32_MAX;
            int minStartVertex = -1;
            int minEndVertex = -1;
            for(visited->first(); visited->isItem(); visited->next()) {
                int startVertex = visited->getActual()->value;
                for(int i = 0; i < m->getCols(); i++) {
                    int weight = m->get(startVertex, i);
                    if(weight < min && visited->find(i) == -1) {
                        min = weight;
                        minEndVertex = i;
                        minStartVertex = startVertex;
                    }
                }
            }

            Vector3 edge;
            edge.x = minStartVertex;
            edge.y = minEndVertex;
            edge.z = min;

            return edge;
        }

    Vector3 findMinEdge(DoubleSidedList<int>* visited, ListsOfNeighbors* l) {
            int min = INT32_MAX;
            int minStartVertex = -1;
            int minEndVertex = -1;
            for(visited->first(); visited->isItem(); visited->next()) {
                int startVertex = visited->getActual()->value;
                for(int i = 0 ; i < l->getNumberOfNeighbors(startVertex); i++) {
                    Vector2 e = l->getEdge(startVertex, i);
                    if(e.y < min && visited->find(e.x) == -1) {
                        min = e.y;
                        minStartVertex = startVertex;
                        minEndVertex = e.x;
                    }
                }
            }

            Vector3 edge;
            edge.x = minStartVertex;
            edge.y = minEndVertex;
            edge.z = min;

            return edge;
        }
    };
};