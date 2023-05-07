#include "ui/UserInterface.h"
#include "ui/ConsoleUI.h"
#include "exception/Exception.h"
#include "structures/Matrix.h"

using namespace std;
using namespace SDIZO;

template<typename T>
void printMatrix(Matrix<T>& matrix) {
    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.getCols(); ++j) {
            std::cout << matrix(i, j) << " ";
        }
        std::cout << std::endl;
    }
}


int main (int argc, char* argv[]) {   
    UserInterface::setInstance(new ConsoleUI());
    UserInterface* ui = UserInterface::getInstance();

    Matrix<int> mat = Matrix<int>::create(3, 3, [](int i, int j) -> int {
        return 42;
    });

    return 0;
} 