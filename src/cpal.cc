#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "../json/src/json.hpp"
#include "cpal.hpp"
using json = nlohmann::json;
typedef unsigned int uint;

struct configuration {
    std::string ssid;
    std::string username;
    std::string password;
    uint auto_login;
    uint wifi_mode;
};

std::string get_input(std::string prompt) {
    std::cout << prompt << "?" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void write_configuration(std::string conf) {
    std::string ssid = get_input("SSID");
    std::string username = get_input("Username");
    std::string password = get_input("Password");
    uint al = (uint)std::stoi(get_input("Auto login (0 = False, 1 = True)"));
    uint wm = (uint)std::stoi(get_input("WiFi mode (0 = False, 1 = True)"));
    configuration c = { ssid, username, password, al, wm };
    json j;
    j["ssid"] = c.ssid;
    j["username"] = c.username;
    j["password"] = c.password;
    j["auto_login"] = c.auto_login;
    j["wifi_mode"] = c.wifi_mode;
    std::ofstream file;
    file.open(conf);
    file << j.dump() << std::endl;
    file.close();
}

void display_version() {
    std::cout << "cpal v. 0.1.0" << std::endl;
    std::cout << "This program uses libcurl (https://curl.haxx.se)" << std::endl;
    exit(0);
}

void display_error(std::string program, std::string err) {
    std::cout << "Error: " << err << ".\n" << std::endl;
    display_usage(program, -1);
}

void display_usage(std::string program, int code) {
    std::cout << "cpal (Captive Portal Auto Login)." << std::endl;
    std::cout << "Utility to automatically log in to a captive portal." << std::endl;
    std::cout << "\nReleased under the MIT License." << std::endl;
    std::cout << "\nUsage: " << program << " <command> [<options>]" << std::endl;
    exit(code);
}

int main(int argc, char *argv[]) {
    std::string program = argv[0];

    // -----------------------------------
    std::string conf_json = ".cpal.json";
    // -----------------------------------

    bool verbose = true;
    int op = -1;
    
    if(argc > 1) {
        for(auto i = 1; i < argc; i++) {
            if(argv[i] == "--help") {
                display_usage(program, 0);
            }
            if(argv[i] == "configure") {
                op = 0;
                break;
            }
        }
    }

    switch(op) {
        case 0:
            write_configuration(conf_json);
            break;
        default:
            break;
    }

    display_usage(program, 0);
    //write_configuration(conf_json);
    return 0;
}
