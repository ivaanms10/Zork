#include "World.h"
#include "Utils.h"
#include <iostream>

int main() {
	std::cout << "Welcome to MyZork!" <<std::endl;
	World* newWorld = new World();
	std::vector<std::string> partsCommand;

	while (true) {
		std::cout << "\n>  ";
		partsCommand = Utils::getPartCommand();
		if (!partsCommand.empty()) {
			if (partsCommand[0] == "Exit") {
				std::cout << "Thank you for playing MyZork Game!." << std::endl;
				break;
			}
			newWorld->processCommand(partsCommand);
		}
	}

	delete newWorld;
	return 0;
}