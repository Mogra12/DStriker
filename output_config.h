#ifndef OUTPUT_CFG
#define OUTPUT_CFG

#include <iostream>

struct Out_color {
    std::string red;
    std::string green;
    std::string yellow;
    std::string b_white;
    std::string reset;
};

Out_color colors() {
    Out_color colors;
    
    colors.red      = "\033[1;31m";
    colors.green    = "\033[1;32m";
    colors.yellow   = "\033[1;33m";
    colors.b_white  = "\033[1;37m";
    colors.reset    = "\033[0m";

    return colors;
}
#endif
