#include "World.h"
#include "Utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

int main() {
	srand(time(NULL));
	std::cout << "==================================================" << std::endl;
	std::cout << "                Welcome to MyZork!                " <<std::endl;
	std::cout << "==================================================" << std::endl;
	World* newWorld = new World();
	std::vector<std::string> partsCommand;

	while (true) {
		std::cout << "\n\n>  ";
		partsCommand = Utils::getPartCommand();
		if (!partsCommand.empty()) {
			if (partsCommand[0] == "Exit") {
				break;
			}
			newWorld->processCommand(partsCommand);
			newWorld->Update();
		}
	}

	std::cout << "Thank you for playing MyZork Game!." << std::endl;
	delete newWorld;
	return 0;
}