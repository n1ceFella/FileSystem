//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           17.03.2022
//==============================================

#ifndef SDDS_FILE_H
#define SDDS_FILE_H
#include <string>
#include "Resource.h"
namespace sdds
{
	class File : public Resource {
	private:
		std::string m_contents{};
	public:
		File(std::string fileName, std::string contents = "");
		void update_parent_path(const std::string&);
		std::string name() const;
		int count() const;
		std::string path() const;
		size_t size() const;
		NodeType type() const;
	};
}
#endif