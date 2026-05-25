#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>


class Utils{
	public: 
		static std::vector<std::string> getPartCommand();
		static std::string getFullNameItem(const std::vector<std::string>& command,  int endName);
};

#endif // !UTILS_H