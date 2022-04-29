#define  _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>

#include <filesystem>
#include "Filesystem.h"
#include "Directory.h"
#include "File.h"
#include "Utilities.h"
namespace fs = std::filesystem;

using namespace sdds;

void init(std::string path, Directory* workingDir) {
    //TO DO: Iterate through all files in foulder and create instances if not exist
    for (const auto& entry : fs::directory_iterator(path)) {
        std::string fname{ entry.path().filename().u8string() };
        Resource* res{};
        if (fname.find('.') == std::string::npos) {
            fname += "/";
            res = new Directory(fname);
            *workingDir += res;
            init(res->path(), workingDir);
        }
        else {
            res = new File(fname);
            *workingDir += res;
        } 
        


        //workingDir->find(fname, oflags);
    }

    //if (workingDir->count() > 0) {

    //}
}


int main(int argc, char** argv)
{

    bool exit = false;
    std::string input;
    std::string path = argv[1];
    sdds::Filesystem fs(path);
    sdds::Directory* workingDir = fs.get_current_directory();
    std::vector<sdds::OpFlags> oflags;
    oflags.push_back(sdds::OpFlags::RECURSIVE);
    //sdds::Directory* t = new sdds::Directory("temp/");
    //*workingDir += t;


    init(path, workingDir);

    logEntry();

    
    while (!exit) {
        std::cout << "$ ";
        getline(std::cin, input, '\n');
        input = input.substr(findChar(input, ' '));
        if (input == "ls") {
            for (const auto& entry : fs::directory_iterator(workingDir->path())) {
                std::string fname{ entry.path().filename().u8string() };
                std::cout << fname << " ";
            }
            std::cout << std::endl;
        }
        else if (input == "cd") {
            workingDir = fs.change_directory("system/");
            //path = argv[1];
        }
        else if (input[0] == 'c' && input[1] == 'd' && input[2] == ' ') {
            workingDir = fs.change_directory(input.substr(3) + "/");
            //path = path + "/" + input.substr(3);
        }
        else if (input == "pwd") {
            //std::cout << path << std::endl;
            std::cout << workingDir->path() << std::endl;
        }
        else if (input.substr(0,5) == "mkdir") {
            //create phusical directory here
            fs::create_directory(workingDir->path() + input.substr(6));

            sdds::Directory* t = new sdds::Directory(input.substr(6) + "/");
            *workingDir += t;
        }
        else if (input.substr(0, 5) == "touch") {
                //create phusical directory here
            std::ofstream file(workingDir->path() + input.substr(6));

            sdds::File* f = new sdds::File(input.substr(6));
            *workingDir += f;
        }
        else if (input == "exit")
            exit = true;

        else
            std::cout << "-bash: " << input << ": command not found" << std::endl;;
    }
}