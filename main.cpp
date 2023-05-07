#include "ui/UserInterface.h"
#include "ui/ConsoleUI.h"
#include "exception/Exception.h"
#include "structures/Matrix.h"
#include "structures/ListsOfNeighbors.h"
#include "app/GraphPrinter.h"
#include "app/GraphReader.h"

using namespace std;
using namespace SDIZO;

int main (int argc, char* argv[]) {   
    UserInterface::setInstance(new ConsoleUI());
    UserInterface* ui = UserInterface::getInstance();

    GraphPrinter gp(ui);
    GraphReader gr(new FileReader("test"), true);
    gp.printMatrix(gr.readMatrix());

    return 0;
} 