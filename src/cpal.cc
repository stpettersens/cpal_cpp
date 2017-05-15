#include <iostream>
#include <string>
#include <cstdlib>
#include "cpal.h"
using namespace std;

void write_configuration(string conf) {

}

void display_version() {
  cout << "cpal v. 0.1.0" << endl;
  cout << "This program uses libcurl (https://curl.haxe.se)" << endl;
  exit(0);
}

void display_error(string program, string err) {
  cout << "Error: " << err << ".\n" << endl;
  display_usage(program, -1);
}

void display_usage(string program, int code) {
  cout << "cpal (Captive Portal Auto Login)." << endl;
  cout << "Utility to automatically log in to a captive portal." << endl;
  cout << "Copyright 2017 Sam Saint-Pettersen." << endl;
  cout << "\nReleased under the MIT License." << endl;
  cout << "\nUsage: " << program << " <command> [<options>]" << endl;
  exit(code);
}

int main(int argc, char *argv[]) {
  string program = "cpal";
  display_usage(program, 0);
  return 0;
}
