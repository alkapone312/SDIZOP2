#include <iostream>
#include <string>
#include "structures/Matrix.h"
#include "utils/FileWriter.h"
#include "utils/RandomNumberGenerator.h"

using namespace std;

namespace SDIZO {
    class GraphGenerator {
    private: 
        FileWriter* writer;    
        bool directed;    
    public:
        GraphGenerator(FileWriter* w, bool d = true): writer(w), directed(d) {}

        void generateGraph(int n, double density) {
            int numberOfEdges = int(density * n * (n-1));
            RandomNumberGenerator r(0, n-1); 
            RandomNumberGenerator weightGenerator(0, 10000000);
            Matrix<int> m = Matrix<int>::create(n, n, [](int row, int col) -> int {
                return INT32_MAX;
            });
            int src = r.nextInt();
            int dst = r.nextInt();

            for (int i = 0; i < numberOfEdges; i++) {
                int src, dst;
                do {
                    src = r.nextInt();
                    dst = r.nextInt();
                } while (src == dst || m.get(src, dst) != INT32_MAX);
                m.set(src, dst, weightGenerator.nextInt());
                if(!directed) {
                    m.set(src, dst, weightGenerator.nextInt());
                }
            }
            // first line with graph info
            writer->write(
                to_string(numberOfEdges) 
                + " " 
                + to_string(n) 
                + " "
                + to_string(r.nextInt()) 
                + " " 
                + to_string(r.nextInt())
                + "\n"
            );
            // write each edge
            for(int i = 0 ; i < n; i++) {
                for(int j = 0 ; j < n; j++) { 
                    int weight = m.get(i, j);
                    if(weight == INT32_MAX) {
                        continue;
                    }
                    writer->write(
                        to_string(i) 
                        + " "
                        + to_string(j)
                        + " "
                        + to_string(weight)
                        + "\n"
                    );
                }
            }
        }

    };
};
