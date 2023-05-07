#pragma once
#include "structures/DoubleSidedList.h"
#include "structures/DynamicArray.h"
#include "structures/Vector.h"

namespace SDIZO {
    class ListsOfNeighbors {
    private:
        DynamicArray<DoubleSidedList<Vector2>*>* listsOfNeighbors = new DynamicArray<DoubleSidedList<Vector2>*>();
    public:
        ListsOfNeighbors(int numberOfVertices) {
            for(int i = 0 ; i < numberOfVertices; i++) {
                listsOfNeighbors->pushBack(new DoubleSidedList<Vector2>());
            }
        }

        ~ListsOfNeighbors() {
            delete listsOfNeighbors;
        }

        void addEdge(int startVertex, int endVertex, int weight) {
            checkStartVertex(startVertex);
            try {
                checkEdge(startVertex, endVertex);
                throw new Exception("Edge already exist!");
            } catch (Exception* ignored) {
                Vector2 edge;
                edge.x = endVertex;
                edge.y = weight; 
                listsOfNeighbors->get(startVertex)->pushBack(edge);
            }
        }

        void removeEdge(int startVertex, int endVertex) {
            checkEdge(startVertex, endVertex);
            DoubleSidedList<Vector2>* tmp = listsOfNeighbors->get(startVertex);
            tmp->remove(findEdge(tmp, endVertex));
        }

        int getNumberOfVertices() {
            return listsOfNeighbors->getLength();
        }

        int getNumberOfNeighbours(int vertexIndex) {
            checkStartVertex(vertexIndex);

            return listsOfNeighbors->get(vertexIndex)->getLength();
        }

        Vector2 getEdge(int startVertex, int index) {
            checkEdge(startVertex, index);

            return listsOfNeighbors->get(startVertex)->get(index);
        } 

    private:    

        void checkEdge(int startVertex, int endVertex) {
            checkStartVertex(startVertex);
            DoubleSidedList<Vector2>* tmp = listsOfNeighbors->get(startVertex);
            if(findEdge(tmp, endVertex) == -1) {
                throw new Exception("Edge does not exist!");
            }
        }

        void checkStartVertex(int vertex) {
            if(listsOfNeighbors->getLength() <= vertex && vertex < 0) {
                throw new Exception("Vertex does not exist!");
            }
        }

        int findEdge(DoubleSidedList<Vector2>* list, int endVertex) {
            int i = 0;
            for(list->first(); list->isItem(); list->next()) {
                if(list->getActual()->value.x == endVertex) {
                    return i;
                }
                i++;
            } 

            return -1;
        }
    };
};