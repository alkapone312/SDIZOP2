#include "utils/FileWriter.h"

using namespace SDIZO;
using namespace std;

FileWriter::FileWriter(string filename, int mode) {
    switch (mode)
    {
    case FileWriter::Mode::CREATE: 
        this->file.open(filename);
        break;
    case FileWriter::Mode::APPEND:
        this->file.open(filename, std::ios_base::app); 
    default:
        break;
    }
}

FileWriter::~FileWriter() {
    this->file.close();
}

void FileWriter::write(string value) {
    this->file << value;
}