//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           17.03.2022
//==============================================

#ifndef SDDS_DIR_H
#define SDDS_DIR_H
#include <string>
#include <vector>
#include "Resource.h"
namespace sdds
{
	class Directory : public Resource
	{
	private:
		std::vector<Resource*> m_contents;
	public:
		Directory(std::string dirName);
		void update_parent_path(const std::string&);
		std::string name() const;
		int count() const;
		std::string path() const;
		size_t size() const;
		NodeType type() const;
		Directory& operator+=(Resource* res);
		Resource* find(const std::string& name, const bool recursive = false);
		void remove(const std::string& name, const bool recursive = false);
		void display(std::ostream& ostr, const bool recursive = false) const;
		~Directory();
		Directory(const Directory& rightOperand) = delete; // copy constructor
		Directory& operator=(const Directory& rightOperand) = delete; // copy assignment operator
		Directory(Directory&& rightOperand) = delete;  // move copyconstructor
		Directory& operator=(Directory&& rightOperand) = delete; // move assignment operator
	};
}
#endif