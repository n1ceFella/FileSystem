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
	Filesystem::Filesystem(std::string path, std::string root) {
	//create root directory
	m_root = new Directory(root);
		size_t start_pos{};
		size_t end_pos{};
		//set current to root directory
		m_current = m_root;

		start_pos = 0;
		end_pos = 0;

		while (path.find('/') != string::npos) {
			string temp;
			end_pos = path.find('/');
			temp = path.substr(start_pos, end_pos + 1);
			//find directory
			Directory* dir = dynamic_cast<Directory*>(m_current->find(temp));
			//if not found, create it and add to current directory, otherwise set it to current
			if (!dir) {
				dir = new Directory(temp); //might be RECURSIVE as it is folder
				operator+=(dir); //might be root instead of current
				m_current = dir;
			}
			else m_current = dir;
			path = path.substr(end_pos + 1);
		}

	}

	//change dirrectory only if it exists
	Directory* Filesystem::change_directory(const std::string& name) {
		std::vector<sdds::OpFlags> oflags;
		oflags.push_back(sdds::OpFlags::RECURSIVE);
		if (name.empty()) {
			m_current = m_root;
		}
		else {
			Directory* newDir = dynamic_cast<Directory*>(m_root->find(name, true));
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