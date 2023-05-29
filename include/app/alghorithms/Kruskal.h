#pragma once
#include "exception/Exception.h"
#include "structures/Matrix.h"
#include "structures/ListsOfNeighbors.h"
#include "app/alghorithms/AlghorithmResult.h"

namespace SDIZO {
    class Kruskal {
    private:
        DynamicArray<Vector3>* edges;
    public:
        Kruskal() {}

        AlghorithmResult* solve(Matrix<int>* m) {
            // fetch edges from matrix and solve with list of edges
            edges = new DynamicArray<Vector3>;
            m->forEach([=](int row, int col, int weight) -> void {
                if(col <= row) {
                    return;
                }

                if(weight != INT32_MAX) {
                    Vector3 edge; edge.x = row; edge.y = col; edge.z = weight;
                    edges->pushBack(edge);
                }
            });

            return kruskal(m->getRows());
        }

        AlghorithmResult* solve(ListsOfNeighbors* l) {
            // fetch edges from lists and solve with list of edges
            edges = new DynamicArray<Vector3>;
            for(int i = 0; i < l->getNumberOfVertices(); i++) {
                for(int j = 0; j < l->getNumberOfNeighbors(i); j++) {
                    Vector2 neighbor = l->getEdge(i, j);
                    if(checkEdges(i, neighbor.x)) {
                        Vector3 newEdge;
                        newEdge.x = i;
                        newEdge.y = neighbor.x;
                        newEdge.z = neighbor.y;
                        edges->pushBack(newEdge);
                    }
                }
            }

            return kruskal(l->getNumberOfVertices());
        }

    private:
        AlghorithmResult* kruskal(int numberOfVertices) {
            AlghorithmResult* result = new AlghorithmResult();
            result->addToResult("Edge   Weight");
            result->startTime();
            //sort edges (quicksort)
            sortEdges();

            //vertices to know which edge belongs to wich tree
            int vertices[numberOfVertices] = {};
            for (int i = 0; i < numberOfVertices; i++) {
                vertices[i] = i;
            }

            //count how many vertices are connected
            int count = 0;
            for (int i = 0; i < edges->getLength(); i++) {
                int u = edges->get(i).x;
                int v = edges->get(i).y;
                int w = edges->get(i).z;
                //if both not in actual tree, add edge to tree
                if (findParent(vertices, u) != findParent(vertices, v)) {
                    result->addToResult("(" + std::to_string(u) + ", " + std::to_string(v) + ") " + std::to_string(w));
                    result->addToMSTSum(w);
                    vertices[findParent(vertices, u)] = findParent(vertices, v);
                    count++;
                    if (count == numberOfVertices - 1) break;
                }
            }
            result->stopTime();

            return result;
        }

        bool checkEdges(int a, int b) {
            for(edges->first(); edges->isItem(); edges->next()) {
                Vector3 e = edges->getActual();
                if((e.x == a && e.y == b) || e.x == b && e.y == a) {
                    return false;
                }
            }

            return true;
        }

        // złożonśc O(logn)
        int findParent(int vertices[], int x) {
            if (vertices[x] == x) {
                return x;
            }

            return vertices[x] = findParent(vertices, vertices[x]);
        }

        void sortEdges() {
            quicksort(edges, 0, edges->getLength()-1);
        }

        void quicksort(DynamicArray<Vector3>* arr, int left, int right) {
            if (left < right) {
                int pivot = partition(arr, left, right);
                quicksort(arr, left, pivot - 1);
                quicksort(arr, pivot + 1, right);
            }
        }

        int partition(DynamicArray<Vector3>* arr, int left, int right) {
            Vector3 pivot = arr->get(right);
            int leftwall = left - 1;

            for(int i = left; i < right; i++) {
                if(compare(arr->get(i), pivot)) {
                    leftwall++;
                    swap(arr, leftwall, i);
                }
            }

            swap(arr, leftwall + 1, right);

            return leftwall + 1;
        }

        void swap(DynamicArray<Vector3>* arr, int a, int b) {
            if(a == b) {
                return;
            }
            Vector3 buff = arr->get(a);
            arr->set(a, arr->get(b));
            arr->set(b, buff);
        }

        bool compare(Vector3 a, Vector3 b) {
            return a.z < b.z;
        }
    };
};