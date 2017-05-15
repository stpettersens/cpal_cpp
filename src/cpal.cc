#include <iostream>
#include <string>
#include <cstdlib>
#include "cpal.hpp"
using namespace std;

void write_configuration(string conf) {
    // ...
}

void display_version() {
    cout << "cpal v. 0.1.0" << endl;
    cout << "This program uses libcurl (https://curl.haxx.se)";
    exit(0);
}

void display_error(string program, string err) {
    cout << "Error: " << err << ".\n" << endl;
    display_usage(program, -1);
}

void display_usage(string program, int code) {
    cout << "cpal (Captive Portal Auto Login)." << endl;
    cout << "Utility to automatically log in to a captive portal." << endl;
    cout << "\nReleased under the MIT License." << endl;
    cout << "\nUsage: " << program << " <command> [<options>]" << endl;
    exit(code);
}

int main(int argc, char *argv[]) {
    string program = "cpal";

    // -------------------------------
    string conf_json = ".cpal.json";
    // -------------------------------

    bool verbose = true;
    int op = -1;

    switch(op) {
        case 0:
            write_configuration(conf_json);
            break;
        default:
            break;
    }

    display_usage(program, 0);
    return 0;
}
