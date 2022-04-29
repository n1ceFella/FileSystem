#ifndef SDDS_UTIL_H
#define SDDS_UTIL_H
#include <iostream>
#include <fstream> 
#include <chrono>
#include <ctime> 
#include <filesystem>
#include "Filesystem.h"
#include "Directory.h"
#include "File.h"

namespace sdds
{
	static size_t findChar(std::string str, char ch, bool reversed = false) {
		if (reversed) {
			for (size_t i = str.length() - 1; i >= 0; i--)
			{
				if (str[i] != ch)
					return i;
			}
		}
		for (size_t i = 0; i < str.length(); i++)
		{
			if (str[i] != ch)
				return i;
		}
		return 0;
	}
    static void init(std::string path, Directory* workingDir) {
        //TO DO: Iterate through all files in folder and create instances if not exist
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
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
        }
    }
	static std::string getDate() {
		auto start = std::chrono::system_clock::now();
		// Some computation here
		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds = end - start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		std::string time = std::ctime(&end_time);

		//std::cout << "Last login: " << std::ctime(&end_time) << std::endl;
		return "Last login: " + time;
	}
	static void logEntry() {
        std::fstream f;
        //read last login time
        f.open("log.txt");
        while (!f.eof()) {
            std::string login;
            getline(f, login);
            std::cout << login << std::endl;

        }
        f.close();
        //write current login time
        f.open("log.txt");
        if (f.is_open()) {
            f << getDate();
            f.close();
        }
	}
}

#endif