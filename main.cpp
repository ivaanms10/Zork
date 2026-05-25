#include "World.h"
#include "Player.h"
#include "Utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

int main() {
	srand(time(NULL));
	std::cout << "==================================================" << std::endl;
	std::cout << "                Welcome to Zork!                " <<std::endl;
	std::cout << "==================================================" << std::endl;

	World* newWorld = new World();
	std::vector<std::string> partsCommand;

	while (newWorld->getPlayer()->getHealth() != 0) {
		std::cout << "\n\n>  ";
		partsCommand = Utils::getPartCommand();
		if (!partsCommand.empty()) {
			if (partsCommand[0] == "exit") {
				break;
			}
			newWorld->processCommand(partsCommand);
			newWorld->Update();
		}
	}

	delete newWorld;
	return 0;
}