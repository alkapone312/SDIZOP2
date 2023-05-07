#include "exception/Exception.h"
#include "ui/UserInterface.h"

using namespace SDIZO;

UserInterface* UserInterface::instance = nullptr;

UserInterface::UserInterface() {
    UserInterface::instance = nullptr;
}

UserInterface::~UserInterface() {}

UserInterface* UserInterface::getInstance() {
    if(UserInterface::instance != nullptr) {
        return UserInterface::instance;
    }

    throw new Exception((char*)"UserInterface instance has not been set!");
}

void UserInterface::setInstance(UserInterface* instance) {
    if(UserInterface::instance == nullptr) {
        UserInterface::instance = instance;
        return;
    }

    throw new Exception((char*)"UserInterface instance already set!");
}