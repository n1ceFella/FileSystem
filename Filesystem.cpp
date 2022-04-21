//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           17.03.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "Filesystem.h"
#include "Directory.h"
#include "File.h"
#include "Utilities.h"

using namespace std;
namespace sdds
{
	Filesystem::Filesystem(std::string fileName, std::string root) {

		std::ifstream fileToRead(fileName);
		if (!fileToRead)
		{
			throw std::invalid_argument("File cannot be opened.");
		}
		//create root directory
		m_root = new Directory(root);
		size_t count = 0;
		std::string record;
		//count number of lines
		do
		{
			std::getline(fileToRead, record);
			if (fileToRead)
				++count;
		} while (fileToRead);
		//set file to the beginning
		fileToRead.clear();
		fileToRead.seekg(std::ios::beg);

		std::string path;
		std::string content;
		size_t start_pos{};
		size_t end_pos{};

		for (size_t i = 0; i < count; i++)
		{
			//set current to root directory
			m_current = m_root;
			start_pos = 0;
			end_pos = 0;

			//read whole line
			std::getline(fileToRead, record);
			//do this block for folders ('|' abscent)
			if (record.find('|') == string::npos) {
				//read line and delete leading and trailing spaces
				start_pos = findChar(record, ' ');
				record = record.substr(start_pos);
				start_pos = 0;
				record = record.substr(start_pos, findChar(record, ' ', true) + 1);
				//do it while '/' presents
				while(record.find('/') != string::npos){
					string temp;
					end_pos = record.find('/');
					temp = record.substr(start_pos, end_pos + 1);
					//find directory
					Directory* dir = dynamic_cast<Directory*>(m_current->find(temp));
					//if not found, create it and add to current directory, otherwise set it to current
					if (!dir) {
						dir = new Directory(temp); //might be RECURSIVE as it is folder
						operator+=(dir); //might be root instead of current
						m_current = dir;
					}
					else m_current = dir;
					record = record.substr(end_pos + 1);
				}
				
			}
			//do this block for files ('|' presents)
			else {
				//get file path from file line (read until '|')
				string pathName;
				end_pos = record.find('|');
				pathName = record.substr(start_pos, end_pos);
				start_pos = findChar(pathName, ' ');
				pathName = pathName.substr(start_pos);
				start_pos = 0;
				end_pos = findChar(pathName, ' ', true);
				pathName = pathName.substr(start_pos, end_pos + 1);

				start_pos = 0;
				end_pos = 0;
				//create new directory if '/' presents in string
				while (pathName.find('/') != string::npos) {
					string directoryName;
					end_pos = pathName.find('/');
					directoryName = pathName.substr(start_pos, end_pos + 1);
					//find directory
					Directory* dir = dynamic_cast<Directory*>(m_current->find(directoryName));
					//if not found create it and add to current directory, otherwise make it current
					if (!dir) {
						dir = new Directory(directoryName);
						operator+=(dir);
						m_current = dir;
					}else m_current = dir;
					//file name left (ex. cat.jpg)
					pathName = pathName.substr(end_pos + 1);
				}
				//get file content from string
				start_pos = record.find('|');
				record = record.substr(start_pos + 1);
				start_pos = findChar(record, ' ');
				record = record.substr(start_pos);
				start_pos = 0;
				end_pos = findChar(record, ' ', true);
				record = record.substr(start_pos, end_pos + 1);

				//create new file
				File* file = new File(pathName, record);
				//add file to current directory
				operator+=(file);
			}
		}
		//set current directory to root
		m_current = m_root;
	}
	//change dirrectory only if it exists
	Directory* Filesystem::change_directory(const std::string& name) {
		if (name.empty()) {
			m_current = m_root;
		}
		else {
			Directory* newDir = dynamic_cast<Directory*>(m_root->find(name));
			if (!newDir)
				throw std::invalid_argument("Cannot change directory! " + name + " not found!");
			return newDir;
		}
		return m_current;
	}
	Directory* Filesystem::get_current_directory() const {
		return m_current;
	}
	Filesystem& Filesystem::operator+=(Resource* res) {
		*m_current += res;
		return *this;
	}
	// move copyconstructor
	Filesystem::Filesystem(Filesystem&& rightOperand) {
		operator=(std::move(rightOperand));
	}
	// move assignment operator
	Filesystem& Filesystem::operator=(Filesystem&& rightOperand) {
		if (this != &rightOperand) {
			delete m_current;
			delete m_root;

			m_current = rightOperand.m_current;
			m_root = rightOperand.m_root;
			rightOperand.m_root = nullptr;
			rightOperand.m_current = nullptr;
		}
		return *this;
	}
	Filesystem::~Filesystem() {
		delete m_root;
	}
}