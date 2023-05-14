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

int main (int argc, char* argv[]) {   
    UserInterface::setInstance(new ConsoleUI());
    UserInterface* ui = UserInterface::getInstance();
    GraphGenerator gg(new FileWriter("test4")); 
    gg.generateGraph(10, 0.5);
    GraphPrinter gp(ui);
    GraphReader gr(new FileReader("test4"), false);
    gp.printMatrix(gr.readMatrix());
    gp.printList(gr.readList());
    try {

        Kruskal* k = new Kruskal();
        AlghorithmResult r1 = k->solve(gr.readMatrix());
        AlghorithmResult r2 = k->solve(gr.readList());

        Prim* p = new Prim();
        AlghorithmResult r3 = p->solve(gr.readMatrix());
        AlghorithmResult r4 = p->solve(gr.readList());

        Dijkstra* d = new Dijkstra();
        AlghorithmResult r5 = d->solve(gr.readMatrix(), gr.getGraphInfo());
        AlghorithmResult r6 = d->solve(gr.readList(), gr.getGraphInfo());

        BellmanFord* b = new BellmanFord();
        AlghorithmResult r7 = b->solve(gr.readMatrix(), gr.getGraphInfo());
        AlghorithmResult r8 = b->solve(gr.readList(), gr.getGraphInfo());

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

        r1.sortStrings(compare);
        r2.sortStrings(compare);
        r3.sortStrings(compare);
        r4.sortStrings(compare);

        r1.printResult();
        r1.printTime();
        r2.printResult();
        r2.printTime();
        r3.printResult();
        r3.printTime();
        r4.printResult();
        r4.printTime();
        r5.printResult();
        r5.printTime();
        r6.printResult();
        r6.printTime();
        r7.printResult();
        r7.printTime();
        r8.printResult();
        r8.printTime();
    } catch (Exception* e) {
        ui->error(e->getMessage());
    }

    return 0;
} 