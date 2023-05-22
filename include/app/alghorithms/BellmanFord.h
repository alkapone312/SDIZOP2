#include "structures/Matrix.h"
#include "structures/ListsOfNeighbors.h"
#include "app/GraphInfo.h"
#include "app/alghorithms/AlghorithmResult.h"

using std::to_string;

namespace SDIZO {
    class BellmanFord {
    private:
        int* distance;
        int* prev;
        int numberOfVertices;
    public:

        AlghorithmResult solve(Matrix<int>* m, GraphInfo info) {
                AlghorithmResult result;
                int numberOfVertices = m->getRows();
                init(numberOfVertices);
                result.startTime();
                distance[info.startingVertex] = 0;
                result.addToResult("Start: " + to_string(info.startingVertex));
                result.addToResult("Edge | Weight | Path");
                bool wasChange = false;
                for (int i = 1; i < numberOfVertices; i++) {
                    wasChange = false;
                    for( int u = 0 ; u < numberOfVertices; u++) {
                        for (int v = 0; v < numberOfVertices; v++) {
                            int weight = m->get(u, v);
                            if (
                                weight != INT32_MAX
                                && distance[u] != INT32_MAX
                                && distance[u] + weight < distance[v]
                            ) { 
                                prev[v] = u;
                                distance[v] = distance[u] + weight; 
                                wasChange = true;
                            }
                        }
                    }
                    if(!wasChange)
                        break;
                }
                result.stopTime();

                return getResult(result);
        }

        AlghorithmResult solve(ListsOfNeighbors* l, GraphInfo info) {
            AlghorithmResult result;
                int numberOfVertices = l->getNumberOfVertices();
                init(numberOfVertices);
                result.startTime();
                distance[info.startingVertex] = 0;
                result.addToResult("Start: " + to_string(info.startingVertex));
                result.addToResult("Edge | Weight | Path");
                bool wasChange = false;
                for (int i = 1; i < numberOfVertices; i++) {
                    wasChange = false;
                    // foreach edge
                    for(int u = 0 ; u < numberOfVertices; u++) {
                        for(int j = 0 ; j < l->getNumberOfNeighbors(u); j++) {
                            Vector2 edge = l->getEdge(u, j);
                            int v = edge.x;
                            int weight = edge.y;
                            if (
                                weight != INT32_MAX
                                && distance[u] != INT32_MAX
                                && distance[u] + weight < distance[v]
                            ) { 
                                prev[v] = u;
                                distance[v] = distance[u] + weight; 
                                wasChange = true;
                            }
                        }
                    }
                    if(!wasChange)
                        break;
                }
                result.stopTime();

                return getResult(result);
        }

    private:
        void init(int numberOfVertices) {
            this->numberOfVertices = numberOfVertices;
            distance = new int[numberOfVertices];
            prev = new int[numberOfVertices];
            for(int i = 0 ; i < numberOfVertices; i++) {
                distance[i] = INT32_MAX;
                prev[i] = i;
            }
        }

        AlghorithmResult getResult(AlghorithmResult &result) {
            for(int i = 0 ; i < numberOfVertices; i++) {
                std::string path = to_string(i);
                int j = i;
                while(prev[j] != j) {
                    path = to_string(prev[j]) + " " + path;
                    j = prev[j];
                }

                result.addToResult(to_string(i) + " | " + to_string(distance[i]) + " | " + path);
            }
        
            return result;
        }
    };
};