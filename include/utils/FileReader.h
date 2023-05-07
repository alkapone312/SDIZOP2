#pragma once
#include <fstream>
#include "utils/File.h"

namespace SDIZO {
    class FileReader : public SDIZO::File {
        private:
            std::ifstream file;
        public:
            FileReader(std::string fileName);
            ~FileReader();
            virtual int getData();
            virtual bool isData();
    };
}