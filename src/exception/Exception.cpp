#include "exception/Exception.h"

using namespace SDIZO;

Exception::Exception(std::string message) {
    this->message = message;
}

Exception::~Exception() {}

std::string Exception::getMessage() {
    return this->message;
}
