#include "ui/UserInterface.h"
#include "ui/ConsoleUI.h"
#include "exception/Exception.h"
#include "structures/Matrix.h"
#include "structures/ListsOfNeighbors.h"
#include "app/GraphPrinter.h"
#include "app/GraphReader.h"
#include "app/alghorithms/Kruskal.h"
#include "app/alghorithms/Prim.h"

using namespace std;
using namespace SDIZO;

int main (int argc, char* argv[]) {   
    UserInterface::setInstance(new ConsoleUI());
    UserInterface* ui = UserInterface::getInstance();

    GraphPrinter gp(ui);
    GraphReader gr(new FileReader("test"), false);
    gp.printMatrix(gr.readMatrix());
    gp.printList(gr.readList());
    try {
        Kruskal* k = new Kruskal();
        AlghorithmResult r1 = k->solve(gr.readMatrix());
        AlghorithmResult r2 = k->solve(gr.readList());

        Prim* p = new Prim();
        AlghorithmResult r3 = p->solve(gr.readMatrix());
        AlghorithmResult r4 = p->solve(gr.readList());

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
        r2.printResult();
        r3.printResult();
        r4.printResult();
    } catch (Exception* e) {
        ui->error(e->getMessage());
    }

    return 0;
} 