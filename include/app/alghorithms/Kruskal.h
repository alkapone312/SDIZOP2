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

        AlghorithmResult solve(Matrix<int> m) {
            if(m.getRows() != m.getCols()) {
                throw new Exception("Unable to solve, wrong matrix");
            }
            edges = new DynamicArray<Vector3>;
            m.forEach([=](int row, int col, int weight) -> void {
                if(weight != INT32_MAX) {
                    Vector3 edge; edge.x = row; edge.y = col; edge.z = weight;
                    edges->pushBack(edge);
                }
            });
            sortEdges();
            for(edges->first(); edges->isItem(); edges->next()) {
                std::cout << edges->getActual().z << std::endl;
            }
            std::cout << std::endl;
        }

        AlghorithmResult solve(ListsOfNeighbors l) {
            
        }

    private:
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