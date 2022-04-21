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
#include "Directory.h"
#include "Resource.h"
#include "File.h"
using namespace std;
namespace sdds
{
	Directory::Directory(std::string dirName) {
		m_name = dirName;
		m_parent_path += m_name;
	}
	//sets the parent path to the parameter.
	void Directory::update_parent_path(const string& parent_path) {
		m_parent_path = parent_path;
		for (int i = 0; i < count(); i++)
		{
			m_contents[i]->update_parent_path(m_parent_path);
		}
	}
	NodeType Directory::type() const {
		return NodeType::DIR;

	};
	string Directory::path() const {
		return m_parent_path + name();
	}
	std::string Directory::name() const {
		return m_name;
	}
	//number of elements in collection
	int Directory::count() const {
		return static_cast<int>(m_contents.size());
	}
	//return size of all files in directory
	size_t Directory::size() const {
		if (!m_contents.empty()) {
			size_t size = 0;
			for (int i = 0; i < count(); i++)
			{
				size += m_contents[i]->size();
			}
			return size;
		}
		return 0u;
	}
	//add file to directory and update absolute path
	Directory& Directory::operator+=(Resource* res) {
		if (!find(res->name())) {
			m_contents.push_back(res);
			res->update_parent_path(path());
			return *this;
		}
		else throw std::exception();	
	}
	//find file or directory
	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag) {
		Resource* temp{};
		for (auto i : m_contents) {
			if (!flag.empty() && flag[0] == OpFlags::RECURSIVE) {
				if (i->type() == NodeType::DIR)
					temp = dynamic_cast<Directory*>(i)->find(name, flag);
			}
			if (name == i->name())
				return i;
		}
		return temp;
	}
	//remove file or directory
	void Directory::remove(const std::string& name, const std::vector<OpFlags>& flag) {
		Resource* temp{};

		//find address of directory
		temp = find(name, flag);
		//if not found throw exception
		if(!temp)
			throw string(name + " does not exist in DIRECTORY_NAME");
		//if directory check for recursive flag
		if (temp->type() == NodeType::DIR) {
			if(flag.empty())
				throw std::invalid_argument(name + " is a directory.Pass the recursive flag to delete directories.");
		}
		//find element in collection, delete it, dealocate memory
		for (int i = 0; i < count(); i++)
		{
			if (m_contents[i] && temp) {
				if (m_contents[i]->name() == temp->name()) {
					m_contents.erase(m_contents.begin() + i);
					delete temp;
					temp = nullptr;
				}
			}
		}
	}
	//display formatted data
	void Directory::display(std::ostream& ostr, const std::vector<FormatFlags>& flag) const {
		ostr << "Total size: " << size() << " bytes" << endl;
		for (int i = 0; i < count(); i++)
		{
			if (m_contents[i]->type() == NodeType::DIR)
				ostr << "D | ";
			if (m_contents[i]->type() == NodeType::FILE)
				ostr << "F | ";
			ostr.width(15);
			ostr.setf(ios::left);
			ostr << m_contents[i]->name();
			ostr.unsetf(ios::left);
			ostr << " |";
			if (!flag.empty()) {
				ostr.width(3);
				ostr.setf(ios::right);
				if(m_contents[i]->type() == NodeType::DIR)
					ostr << m_contents[i]->count();
				else ostr << ' ';
				ostr << " | ";
				ostr.width(4);
				ostr << m_contents[i]->size();
				ostr << " bytes";
				ostr << " | ";
				ostr.unsetf(ios::right);
			}
			ostr << endl;
		}
	}
	Directory::~Directory() {
		for (auto element : m_contents) {
			delete element;
		}
	}

};