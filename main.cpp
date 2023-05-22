#include "ui/UserInterface.h"
#include "ui/ConsoleUI.h"
#include "exception/Exception.h"
#include "structures/Matrix.h"
#include "structures/ListsOfNeighbors.h"
#include "utils/FileReader.h"
#include "utils/FileWriter.h"
#include "app/GraphGenerator.h"
#include "app/GraphPrinter.h"
#include "app/GraphReader.h"
#include "app/alghorithms/Kruskal.h"
#include "app/alghorithms/Prim.h"
#include "app/alghorithms/Dijkstra.h"
#include "app/alghorithms/BellmanFord.h"

using namespace std;
using namespace SDIZO;

void MST();
void SP();
Matrix<int> readMatrix(string filename, bool directed);
ListsOfNeighbors readList(string filename, bool directed);
bool handleWithArguments(int argc, char* argv[]);
GraphInfo readInfo(string filename);
bool (*compare)(std::string, std::string) = ([](std::string s1, std::string s2) -> bool {
    int pos1 = s1.find_first_of("0123456789");
    int pos2 = s2.find_first_of("0123456789");
    while(s1[pos1] == s2[pos2]) {
        pos1 = s1.find_first_of("0123456789", pos1+1);
        pos2 = s2.find_first_of("0123456789", pos2+2);
    }
    if(pos1 == -1) return true;
    if(pos2 == -1) return false;
    
    int num1 = std::stoi(s1.substr(pos1));
    int num2 = std::stoi(s2.substr(pos2));
    
    return num1 < num2;
});

int main (int argc, char* argv[]) {
    if(handleWithArguments(argc, argv)) {
        return 0;
    }
    
    UserInterface::setInstance(new ConsoleUI());
    UserInterface* ui = UserInterface::getInstance();
    
    bool exit = false;
    while(!exit) {
        string options[] = {
            "1. Minimal spanning tree",
            "2. Shortest path",
            "3. Exit",
            "\0"
        };
        ui->menu(options);
        try {
            switch(ui->getNumber()) {
                case 1:
                    MST();
                break;
                case 2:
                    SP();
                break;
                case 3:
                    exit = true;
                break;
            }
        } catch(Exception* e) {
            ui->error(e->getMessage());
        }
    }

    return 0;
} 

void MST() {
    UserInterface* ui = UserInterface::getInstance();
    string options[] = {
        "1. Display matrix",
        "2. Display list",
        "3. Kruskal",
        "4. Prim",
        "5. Exit",
        "\0"
    };
    bool exit = false;
    ui->message("Please provide filename:");
    string filename = ui->getString();
    Matrix<int> m = readMatrix(filename, false);
    ListsOfNeighbors l = readList(filename, false);
    AlghorithmResult r1;
    AlghorithmResult r2;
    while(!exit) {
        ui->menu(options);
        switch(ui->getNumber()) {
            case 1:
                GraphPrinter(ui).printMatrix(&m);
            break;
            case 2:
                GraphPrinter(ui).printList(&l);
            break;
            case 3:
                ui->info("Result for matrix:");
                r1 = Kruskal().solve(&m);
                r1.sortStrings(compare);
                r1.printResult();
                ui->info("Result for list:");
                r2 = Kruskal().solve(&l);
                r2.sortStrings(compare);
                r2.printResult();
            break;
            case 4:
                ui->info("Result for matrix:");
                r1 = Prim().solve(&m);
                r1.sortStrings(compare);
                r1.printResult();
                ui->info("Result for list:");
                r2 = Prim().solve(&l);
                r2.sortStrings(compare);
                r2.printResult();
            break;
            case 5:
            exit = true;
            break;
        }
    }
}

void SP() {
    UserInterface* ui = UserInterface::getInstance();
    string options[] = {
        "1. Display matrix",
        "2. Display list",
        "3. Dijkstra",
        "4. Bellman ford",
        "5. Exit",
        "\0"
    };
    bool exit = false;
    ui->message("Please provide filename");
    string filename = ui->getString();
    Matrix<int> m = readMatrix(filename, true);
    ListsOfNeighbors l = readList(filename, true);
    GraphInfo g = readInfo(filename);
    AlghorithmResult r1;
    AlghorithmResult r2;
    while(!exit) {
        ui->menu(options);
        switch(ui->getNumber()) {
            case 1:
                GraphPrinter(ui).printMatrix(&m);
            break;
            case 2:
                GraphPrinter(ui).printList(&l);
            break;
            case 3:
                ui->info("Result for matrix:");
                r1 = Dijkstra().solve(&m, g);
                r1.sortStrings(compare);
                r1.printResult();
                ui->info("Result for list:");
                r2 = Dijkstra().solve(&l, g);
                r2.sortStrings(compare);
                r2.printResult();
            break;
            case 4:
                ui->info("Result for matrix:");
                r1 = BellmanFord().solve(&m, g);
                r1.sortStrings(compare);
                r1.printResult();
                ui->info("Result for list:");
                r2 = BellmanFord().solve(&l, g);
                r2.sortStrings(compare);
                r2.printResult();
            break;
            case 5:
            exit = true;
            break;
        }
    }
}

Matrix<int> readMatrix(string filename, bool directed) {
    return GraphReader(new FileReader(filename), directed).readMatrix();
}

ListsOfNeighbors readList(string filename, bool directed) {
    return GraphReader(new FileReader(filename), directed).readList();
}

GraphInfo readInfo(string filename) {
    return GraphReader(new FileReader(filename), false).getGraphInfo();
}

bool handleWithArguments(int argc, char* argv[]) {
    if(argc == 4) {
        UserInterface::setInstance(new ConsoleUI());
        UserInterface* ui = UserInterface::getInstance();
        int numberOfVertices = stoi(argv[1]);
        double graphDensity = stod(argv[2]);
        int loops = stoi(argv[3]);
        string file = to_string(numberOfVertices) + "-" + to_string(graphDensity) + "-" + to_string(loops);

        if(!system("mkdir test-results")) {
            system("mkdir test-results/kruskal");
            system("mkdir test-results/prim");
            system("mkdir test-results/dijkstra");
            system("mkdir test-results/bellmanford");
            system("mkdir test-results/kruskal/matrix");
            system("mkdir test-results/kruskal/list");
            system("mkdir test-results/prim/matrix");
            system("mkdir test-results/prim/list");
            system("mkdir test-results/dijkstra/matrix");
            system("mkdir test-results/dijkstra/list");
            system("mkdir test-results/bellmanford/matrix");
            system("mkdir test-results/bellmanford/list");
        }

        for(int i = 0 ; i < loops; i++) {
            FileWriter* writer1 = new FileWriter(".test", FileWriter::Mode::CREATE);
            FileWriter* writer2 = new FileWriter(".test", FileWriter::Mode::CREATE);

            GraphGenerator directedGraphGenerator(writer1, true);
            directedGraphGenerator.generateGraph(numberOfVertices, graphDensity);
            delete writer1;
            GraphReader directedGraphReader(new FileReader(".test"), false);

            GraphGenerator undirectedGraphGenerator(writer2, false);
            undirectedGraphGenerator.generateGraph(numberOfVertices, graphDensity);
            delete writer2;
            GraphReader unDirectedGraphReader(new FileReader(".test"), false);

            try {
                Matrix<int> undirectedMatrix = unDirectedGraphReader.readMatrix();
                // Matrix<int> directedMatrix = directedGraphReader.readMatrix();
                ListsOfNeighbors undirectedList = unDirectedGraphReader.readList();
                // ListsOfNeighbors directedList = directedGraphReader.readList();

                Kruskal* k = new Kruskal();
                AlghorithmResult r1 = k->solve(&undirectedMatrix);
                AlghorithmResult r2 = k->solve(&undirectedList);

                Prim* p = new Prim();
                AlghorithmResult r3 = p->solve(&undirectedMatrix);
                AlghorithmResult r4 = p->solve(&undirectedList);

                // Dijkstra* d = new Dijkstra();
                // AlghorithmResult r5 = d->solve(&directedMatrix, directedGraphReader.getGraphInfo());
                // AlghorithmResult r6 = d->solve(&directedList, directedGraphReader.getGraphInfo());

                // BellmanFord* b = new BellmanFord();
                // AlghorithmResult r7 = b->solve(&directedMatrix, directedGraphReader.getGraphInfo());
                // AlghorithmResult r8 = b->solve(&directedList, directedGraphReader.getGraphInfo());

                int append = FileWriter::Mode::APPEND;
                (FileWriter("test-results/kruskal/matrix/" + file, append)).write(to_string(r1.getTime()) + "\n");
                (FileWriter("test-results/kruskal/list/" + file, append)).write(to_string(r2.getTime()) + "\n");
                (FileWriter("test-results/prim/matrix/" + file, append)).write(to_string(r3.getTime()) + "\n");
                (FileWriter("test-results/prim/list/" + file, append)).write(to_string(r4.getTime()) + "\n");
                // (FileWriter("test-results/dijkstra/matrix/" + file, append)).write(to_string(r5.getTime()) + "\n");
                // (FileWriter("test-results/dijkstra/list/" + file, append)).write(to_string(r6.getTime()) + "\n");
                // (FileWriter("test-results/bellmanford/matrix/" + file, append)).write(to_string(r7.getTime()) + "\n");
                // (FileWriter("test-results/bellmanford/list/" + file, append)).write(to_string(r8.getTime()) + "\n");
            } catch (Exception* e) {
                ui->error(e->getMessage());
            }
        }
        return true;
    }
    return false;
}