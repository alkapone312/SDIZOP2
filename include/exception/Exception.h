#pragma once
#include <string>

namespace SDIZO {
    class Exception {
        private:
            std::string message;
        public:
            Exception(std::string message);
            ~Exception();
            virtual std::string getMessage();
    };
}