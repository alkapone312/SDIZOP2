#include <iostream>
#include "ui/ConsoleUI.h"

using namespace SDIZO;
using namespace std;

ConsoleUI::ConsoleUI() {}

ConsoleUI::~ConsoleUI() {}

int ConsoleUI::getNumber() {
    string potentialNumber;
    this->message("Please provide a number:");
    cin >> potentialNumber;

    return this->stringToNumber(potentialNumber);
}

string ConsoleUI::getString() {
    this->message("Press enter to accept:");
    string s;
    cin >> s;

    return s;
}

void ConsoleUI::menu(string* options) {
    try {
        int i = 0;
        while(options[i] != "\0") {
            this->message(options[i]);
            i++;
        }
    } catch (...) {}
}

void ConsoleUI::info(string messsage) {
    cout << "Info message: " << messsage << endl;
}

void ConsoleUI::error(string errorMessage) {
    cout << "ERROR: " << errorMessage << endl;
}

void ConsoleUI::message(string message) {
    cout << "Message: " << message << endl;
}

int ConsoleUI::stringToNumber(string potentialNumber) {
    try {
        return stoi(potentialNumber);
    } catch(...) {
        return -1;
    }
}

void ConsoleUI::wait() {
    this->info("Click enter to continue...");
    cin.ignore();
    cin.get();
}