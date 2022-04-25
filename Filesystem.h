//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           17.03.2022
//==============================================

#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H
#include <string>
#include "Directory.h"
namespace sdds
{
	class Filesystem
	{
	private:
		Directory* m_root; 
		Directory* m_current;
	public:
		//Filesystem(std::string fileName, std::string root = "");
		Filesystem(std::string path, std::string root = "");
		Filesystem(const Filesystem& rightOperand) = delete; // copy constructor
		Filesystem& operator=(const Filesystem& rightOperand) = delete; // copy assignment operator
		Filesystem(Filesystem&& rightOperand);  // move copyconstructor
		Filesystem& operator=(Filesystem&& rightOperand); // move assignment operator
		Filesystem& operator+=(Resource* res);
		Directory* change_directory(const std::string& name = "");
		Directory* get_current_directory() const;
		~Filesystem();
	};
}
#endif