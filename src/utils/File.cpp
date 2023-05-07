#include <fstream>
#include "utils/File.h"

using namespace SDIZO;
using namespace std;

bool File::fileExists(std::string fileName) {
    ifstream f(fileName);
    bool ok = f.good();
    f.close();
    
    return ok;
}