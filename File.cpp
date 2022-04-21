//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           17.03.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Flags.h"
#include "File.h"
using namespace std;
namespace sdds
{
	File::File(string fileName, string contents) : m_contents { contents } {
		m_name = fileName;
	}
	//sets the parent path to the parameter.
	void File::update_parent_path(const string& parent_path) {
		m_parent_path = parent_path; //m_name might be redundant
	} 
	NodeType File::type() const {
		return NodeType::FILE;
		
	};
	string File::path() const {
		return m_parent_path + name(); //check it
	}
	std::string File::name() const {
		return m_name;
	}
	int File::count() const {
		return -1;
	}
	size_t File::size() const {
		return m_contents.length();
	}
}