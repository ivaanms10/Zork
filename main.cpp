#include "World.h"


int main() {
	std::cout << "Welcome to MyZork!" <<std::endl;
	World* newWorld = new World();
	std::vector<std::string> partsCommand;

	while (true) {
		std::cout << "\n>  ";
		partsCommand = Utils::getPartCommand();
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