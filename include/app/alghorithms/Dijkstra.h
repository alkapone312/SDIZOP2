#include "exception/Exception.h"
#include "structures/BinaryHeap.h"
#include "structures/Vector.h"
#include "structures/Matrix.h"
#include "structures/ListsOfNeighbors.h"
#include "app/alghorithms/AlghorithmResult.h"
#include "app/GraphInfo.h"

using namespace std;

namespace SDIZO {
    class Dijkstra {
        private:
            bool* shortestPathTree;
            int* distance;
            int* prev;
            int numberOfVertices;
        public:
            Dijkstra() {}

            // O(V^2)
            AlghorithmResult* solve(Matrix<int>* m, GraphInfo info) {
                AlghorithmResult* result = new AlghorithmResult();
                init(m->getRows());
                
                for (int i = 0; i < numberOfVertices; i++)
                    distance[i] = INT32_MAX, shortestPathTree[i] = false;
            
                distance[info.startingVertex] = 0;
                result->addToResult("Start: " + to_string(info.startingVertex));
                result->addToResult("End | Dist | Path");          
                result->startTime();
                // O(V)
                for (int count = 0; count < numberOfVertices; count++) {
                    int u = minDistance();
                    shortestPathTree[u] = true;
                    string row = to_string(u) + " | " + to_string(distance[u]) + " | ";
                    // O(V)
                    for (int v = 0; v < numberOfVertices; v++) {
                        if (
                            !shortestPathTree[v] 
                            && m->get(u, v) != INT32_MAX
                            && distance[u] != INT32_MAX
                            && distance[u] + m->get(u, v) < distance[v]
                        ) {
                            distance[v] = distance[u] + m->get(u, v);
                            prev[v] = u;
                        }
                    }
                }
                result->stopTime();

                return getResult(result);
            }

            AlghorithmResult* solve(ListsOfNeighbors* l, GraphInfo info) {
                AlghorithmResult* result = new AlghorithmResult();
                BinaryHeap<Pair<int, int>> pq;
                init(l->getNumberOfVertices());
                
                Pair<int, int> p(info.startingVertex, 0);
                pq.push(p);
                distance[info.startingVertex] = 0;
                result->addToResult("Start: " + to_string(info.startingVertex));
                result->addToResult("End | Dist | Path");   
            
                result->startTime();
                // O(V)
                while (pq.getLength()) {
                    int u = pq.pop().a;
                    shortestPathTree[u] = true;
                    pq.first();
                    while(pq.isItem() && shortestPathTree[pq.getActual().a]) {
                        pq.pop();
                    }
                    
                    for (int i = 0 ; i < l->getNumberOfNeighbors(u); i++) {
                        // Get vertex label and weight of current
                        // adjacent of u.
                        int v = l->getEdge(u, i).x;
                        int weight = l->getEdge(u, i).y;
            

                        // If there is shorted path to v through u.
                        if (distance[v] > distance[u] + weight) {
                            // Updating distance of v
                            distance[v] = distance[u] + weight;
                            prev[v] = u;
                            Pair<int, int> p(v, distance[v]);
                            pq.push(p);
                        }
                    }   
                }
                result->stopTime();

                return getResult(result);
            }
        
        private:
            void init(int numberOfVertices) {
                this->numberOfVertices = numberOfVertices;
                shortestPathTree = new bool[numberOfVertices];
                distance = new int[numberOfVertices];
                prev = new int[numberOfVertices];
                for(int i = 0 ; i < numberOfVertices; i++) {
                    distance[i] = INT32_MAX;
                    prev[i] = i;
                }
            }

            int minDistance() {
                int min = INT32_MAX;
                int min_index = -1;

                for (int v = 0; v < numberOfVertices; v++)
                    if (shortestPathTree[v] == false && distance[v] <= min)
                        min = distance[v], min_index = v;
            
                return min_index;
            }

            AlghorithmResult* getResult(AlghorithmResult* result) {
                for(int i = 0 ; i < numberOfVertices; i++) {
                    std::string path = to_string(i);
                    int j = i;
                    while(prev[j] != j) {
                        path = to_string(prev[j]) + " " + path;
                        j = prev[j];
                    }

                    result->addToResult(to_string(i) + " | " + to_string(distance[i]) + " | " + path);
                }
            
                return result;
            }
    };
};