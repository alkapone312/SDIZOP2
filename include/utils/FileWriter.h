#pragma once
#include <fstream>
#include "utils/File.h"

namespace SDIZO {
    class FileWriter : public SDIZO::File {
        private:
            std::ofstream file;
        public:
            enum Mode {
                CREATE, APPEND
            };
            FileWriter(std::string filename, int mode = FileWriter::Mode::CREATE);
            ~FileWriter();
            virtual void write(std::string value);
    };
}
