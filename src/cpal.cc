#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <regex>
#include "../json/src/json.hpp"
#include "cpal.hpp"
using json = nlohmann::json;

struct configuration {
    std::string ssid;
    std::string username;
    std::string password;
    int auto_login;
    int wifi_mode;
};

std::string get_input(std::string prompt) {
    std::cout << prompt << "?" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void write_configuration(std::string conf, bool verbose) {
    std::string ssid = get_input("SSID");
    std::string username = get_input("Username");
    std::string password = get_input("Password");
    int al = std::stoi(get_input("Auto login (0 = False, 1 = True)"));
    int wm = std::stoi(get_input("WiFi mode (0 = False, 1 = True)"));
    configuration c = { ssid, username, password, al, wm };
    json j;
    j["ssid"] = c.ssid;
    j["username"] = c.username;
    j["password"] = c.password;
    j["auto_login"] = c.auto_login;
    j["wifi_mode"] = c.wifi_mode;
    std::ofstream file(conf);
    file << j.dump() << std::endl;
    file.close();
    if(verbose) {
        std::cout << "Wrote configuration -> " << conf << std::endl; 
    }
}

configuration load_configuration(std::string conf, bool verbose) {
    json j;
    std::ifstream file(conf);
    file >> j;
    file.close();
    configuration c = {
        j["ssid"].get<std::string>(),
        j["username"].get<std::string>(),
        j["password"].get<std::string>(),
        j["auto_login"].get<int>(),
        j["wifi_mode"].get<int>()
    };
    if(verbose) {
        std::cout << "Loaded configuration <- " << conf << std::endl;
    }
    return c;
}

void print_configuration(configuration c) {
    // ...
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

    // ------------------------------------
    std::string conf_json = ".cpal.json";
    // ------------------------------------

    bool verbose = true;
    int op = -1;
    
    if(argc > 1) {
        for(auto i = 1; i < argc; i++) {
            if(std::regex_match(argv[i], std::regex("-h|--help"))) {
                display_usage(program, 0);
            }
            if(std::regex_match(argv[i], std::regex("-v|--version"))) {
                display_version();
            }
            if(std::regex_match(argv[i], std::regex("-q|--quiet"))) {
                verbose = false;
            }
            if(std::regex_match(argv[i], std::regex("configure"))) {
                op = 0;
                break;
            }
        }
    }
    
    std::ifstream cfile(conf_json);
    if(!cfile.good()) {
        write_configuration(conf_json, verbose);
    }
    
    auto config = load_configuration(conf_json, verbose);
    std::cout << config.ssid << std::endl;
    std::cout << config.username << std::endl;

    switch(op) {
        case 0:
            write_configuration(conf_json, verbose);
            break;
        default:
            break;
    }

    return 0;
}
