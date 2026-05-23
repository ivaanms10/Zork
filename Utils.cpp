#include "Utils.h"
#include <sstream>
#include <iostream>

/*
	@brief Method to slice the command entered by the player.
	@return Vector with the parts of the command.
*/
std::vector<std::string> Utils::getPartCommand() {
	std::string command = "";
	std::getline(std::cin, command);

	std::stringstream parts(command);
	std::string word = "";
	std::vector<std::string> args;
	while (parts >> word) {
		args.push_back(word);
	}

	return args;
}

/*
	@brief Method to get the full name of the items.
	@return String with the full name.
*/
std::string Utils::getFullNameItem(const std::vector<std::string>& command) {
	std::string fullName = "";
	try {
		int num = std::stoi(command.back());
		for (int i = 1; i < command.size()-1; ++i) {
			fullName += command[i];
			if (i < command.size() - 2) {
				fullName += " ";
			}
		}
	}catch (const std::invalid_argument& e) {
		for (int i = 1; i < command.size(); ++i) {
			fullName += command[i];
			if (i < command.size() - 1) {
				fullName += " ";
			}
		}
	}
	
	return fullName;
}