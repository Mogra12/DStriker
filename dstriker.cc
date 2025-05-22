#include <iostream>
#include <string>
#include <fstream>
#include <csignal>
#include <atomic>
#include <chrono>

#include "request.h"
#include "output_config.h"

#ifdef _WIN32
#include <windows.h>

void enableVirtualTerminal() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

Config cfg;
Out_color getColors = colors();

std::atomic<bool> interrupted(false);
unsigned short int counter = 0;

void handleSignal(int signal) {
    if (signal == SIGINT) {
        interrupted = true;
        std::cout << "\n" << getColors.b_white 
                  << "[!] Program aborted! Requests count: " 
                  << getColors.green 
                  << counter 
                  << getColors.reset 
                  << std::endl;
    }
}

int main(int argc , char* argv[]) {
#ifdef _WIN32
    enableVirtualTerminal();    
#endif

    std::string line;
    
    signal(SIGINT, handleSignal);

    for(int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if(arg == "-u" || arg == "--url" && i + 1 < argc) {
            cfg.url = argv[++i];
        } else if(arg == "-wl" || arg == "--wordlist" && i + 1 < argc) {
            cfg.wordlist = argv[++i];
        } else if(arg == "-h" || arg == "--help") {
            std::cout << getColors.yellow 
                      << "Use:"
                      << getColors.green
                      << "  ./dstriker -u " 
                      << getColors.b_white 
                      << "<url> " 
                      << getColors.green
                      << "-wl " 
                      << getColors.b_white 
                      << "<wordlist>\n\n"
                      << "  -u | --url          URL Target\n"
                      << "  -wl| --wordlist     Wordlist path\n"
                      << "  -h | --help         Shows the manual"
                      << std::endl;
            return 0;
        } else if(arg == "--version") {
            std::cout << getColors.b_white 
                      << "Version: 1.1.1"
                      << std::endl;
        }
    }

    if(cfg.url.empty() || cfg.wordlist.empty()) {
        std::cout << getColors.red 
                  << "[ - ] URL or Wordlist path is empty!" 
                  << getColors.reset 
                  << std::endl;
        return 1;
    }

    std::ifstream archive(cfg.wordlist);

    if(!archive.is_open()) {
        std::cerr << getColors.red 
                  << "[ - ] Error to open the archive!" 
                  << getColors.reset 
                  << std::endl;
        return 1;
    }

    std::cout << getColors.green 
              << "[*] Initializing... " 
              << getColors.reset 
              << "\n";

    std::cout << getColors.red 
              << "URL TARGET: " 
              << cfg.url 
              << getColors.reset 
              << std::endl;

    std::cout << getColors.red
              << "WORDLIST PATH: " 
              << cfg.wordlist 
              << getColors.reset 
              << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    while(std::getline(archive , line)) {
        if(interrupted) continue;
        request(cfg, line);
        counter++;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << getColors.b_white 
              << "Elapsed time: "
              << elapsed.count() 
              << " seconds" 
              << std::endl;

    return 0;
}
