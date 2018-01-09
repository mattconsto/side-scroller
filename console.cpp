#include <iostream>
#include "console.h"
#include "consolecolor.h"

Console::Console() {
    std::cout << std::endl << " SideScroller Console " << std::endl << std::endl << "================================================================================" << std::endl;
}

void Console::log(int level, std::string message) {

    if(level < 0 || level > 2)
        level = 3;

    std::string levels[4]  = {"Info", "Warning", "Error", "Unknown"};

    for(int i = 0; i < 7 - levels[level].length(); i++)
        std::cout << " ";

    switch(level) {
        case 1: std::cout << yellow; break;
        case 2: std::cout << red; break;
        default: std::cout << white;
    }

    std::cout << "[" << levels[level] << "] : " << message << std::endl;
}

std::string Console::read(std::string message = "") {
    std::string input = "";

    if(message.length() > 0)
        std::cout << std::endl << green << "            " << message;

    std::cout << std::endl << green << "    Input : ";
    std::cin >> input;
    std::cout << std::endl;
    return input;
}
