#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Utils{
	public: 
		static std::vector<std::string> getPartCommand();
		static std::string getFullNameItem(const std::vector<std::string>& command);

};

#endif // !UTILS_H



