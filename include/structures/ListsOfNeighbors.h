#pragma once
#include "structures/DoubleSidedList.h"
#include "structures/DynamicArray.h"
#include "structures/Vector.h"

namespace SDIZO {
    class ListsOfNeighbors {
    private:
        DynamicArray<DynamicArray<Vector2>*>* listsOfNeighbors = new DynamicArray<DynamicArray<Vector2>*>();
    public:
        ListsOfNeighbors(int numberOfVertices) {
            for(int i = 0 ; i < numberOfVertices; i++) {
                listsOfNeighbors->pushBack(new DynamicArray<Vector2>());
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
            DynamicArray<Vector2>* tmp = listsOfNeighbors->get(startVertex);
            tmp->remove(findEdge(tmp, endVertex));
        }

        int getNumberOfVertices() {
            return listsOfNeighbors->getLength();
        }

        int getNumberOfNeighbors(int vertexIndex) {
            checkStartVertex(vertexIndex);

            return listsOfNeighbors->get(vertexIndex)->getLength();
        }

        Vector2 getEdge(int startVertex, int index) {
            return listsOfNeighbors->get(startVertex)->get(index);
        } 

    private:    

        void checkEdge(int startVertex, int endVertex) {
            checkStartVertex(startVertex);
            DynamicArray<Vector2>* tmp = listsOfNeighbors->get(startVertex);
            if(findEdge(tmp, endVertex) == -1) {
                throw new Exception("Edge does not exist!");
            }
        }

        void checkStartVertex(int vertex) {
            if(listsOfNeighbors->getLength() <= vertex && vertex < 0) {
                throw new Exception("Vertex does not exist!");
            }
        }

        int findEdge(DynamicArray<Vector2>* arr, int endVertex) {
            int i = 0;
            for(arr->first(); arr->isItem(); arr->next()) {
                if(arr->getActual().x == endVertex) {
                    return i;
                }
                i++;
            } 

            return -1;
        }
    };
};