#define  _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>

#include <filesystem>
#include "Utilities.h"
namespace fs = std::filesystem;

using namespace sdds;
int main(int argc, char** argv)
{

    bool exit = false;
    std::string input;
    std::string path = argv[0];

    logEntry();

    while (!exit) {
        getline(std::cin ,input, '\n');
        if (input == "ls") {
            //path = "D:\\system";
            for (const auto& entry : fs::directory_iterator(path)) {
                std::cout << entry.path().filename() << " ";
            }
            std::cout << std::endl;
        }
        else if (input == "cd") {
            getline(std::cin, path, '\n');
            std::cout << path;
        }
        else if (input == "exit")
            exit = true;
    }
}