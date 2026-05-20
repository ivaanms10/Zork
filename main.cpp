#include "World.h"
#include <sstream>

/*
	@brief Method to slice the command entered by the player.
	@return Vector with the parts of the command.
*/
std::vector<std::string>getPartCommand() {
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


int main() {
	std::cout << "Welcome to MyZork!" <<std::endl;
	World* newWorld = new World();
	std::vector<std::string> partsCommand;

	while (true) {
		std::cout << "\n>";
		partsCommand = getPartCommand();
		if (!partsCommand.empty()) {
			if (partsCommand[0] == "Exit") {
				break;
			}
			newWorld->processCommand(partsCommand);
		}
	}

	delete newWorld;
	return 0;
}