#pragma once
#include <string>
#include <iostream>
using std::string;
using std::endl;
using std::cout;

class Logger {
    void print(string out) {
        cout << out;
    }

    void printl(string out) {
        cout << out << endl;
    }
};

