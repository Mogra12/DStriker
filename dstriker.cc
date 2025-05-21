#include <iostream>
#include <string>
#include <fstream>
#include "request.h"

int main(int argc , char* argv[]) {
    Config cfg;
    std::string line;

    for(int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if(arg == "-u" && i + 1 < argc) {
            cfg.url = argv[++i];
        } else if(arg == "-wl" && i + 1 < argc) {
            cfg.wordlist = argv[++i];
        }
    }

    if(cfg.url.empty() || cfg.wordlist.empty() == true) {
        std::cout << "URL or Wordlist path is empty!" << std::endl;
    }

    std::ifstream archive(cfg.wordlist);

    if(!archive.is_open()) {
        std::cerr << "Error to open the archive!" << std::endl;
        return 1;
    }

    while(std::getline(archive, line)) {
        request(cfg, line);
    }

    return 0;
}