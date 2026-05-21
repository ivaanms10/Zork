#include "World.h"

/*
	@brief Default constructor of the World class.
*/
World::World() : player(nullptr){
	createWorld();
}


/*
	@brief Parameterized constructor of the World class.
	@param entities Vector that contains the entities of the world.
*/
World::World(Player* player, std::vector<Entity*> entities) : player(player), entities(entities){
	createWorld();
}


/*
	@brief Destroyer of the World class.
*/
World::~World() {
	for (const auto& it : entities) {
		delete it;
	}
	entities.clear();
}


/*
	@brief Method to create a world with its respective entities.
*/
void World::createWorld() {
	Room* room1 = new Room("Entryway", "A cold stone foyer with a heavy oak portal leading outside.");
	Room* room2 = new Room("Ancient Library", "Shelves of dusty, ancient books filled with forgotten magical lore.");
	Room* room3 = new Room("Sunken Garden", "An outdoor courtyard oasis with lush, exotic plants and a small fountain.");
	Room* room4 = new Room("Great Hall", "A vast banquet hall featuring massive stone pillars and torn banners.");
	Room* room5 = new Room("Rocky Cavern", "A damp limestone cave with glittering stalactites and gravel floors.");
	Room* room6 = new Room("Smuggler's Cove", "A hidden sandy shore with a solitary rowboat resting near the water.");
	Room* room7 = new Room("Locked Treasure", "A reinforced stone vault holding a massive, heavily padlocked chest.");

	Exit* exit1 = new Exit(DirectionType::NORTH, room1, room3,"Exit 1", "Entryway-Sunken Garden"); //Entryway-Sunken Garden
	Exit* exit2 = new Exit(DirectionType::SOUTH, room1, room4, "Exit 2", "Entryway-Great Hall"); //Entryway-Great Hall
	Exit* exit3 = new Exit(DirectionType::EAST, room1, room5, "Exit 3", "Entryway-Rocky Cavern"); //Entryway-Rocky Cavern
	Exit* exit4 = new Exit(DirectionType::WEST, room1, room2, "Exit 4", "Entryway-Ancient Library"); //Entryway-Ancient Library
	Exit* exit5 = new Exit(DirectionType::WEST, room4, room7, "Exit 5", "Great Hall-Locked Treasure"); //Great Hall-Locked Treasure
	Exit* exit6 = new Exit(DirectionType::NORTH, room6, room3, "Exit 6", "Smuggler's Cove-Sunken Garden"); //Smuggler's Cove-Sunken Garden
	Exit* exit7 = new Exit(DirectionType::SOUTH, room3, room1, "Exit 7", "Sunken Garden-Entryway"); //Sunken Garden-Entryway
	Exit* exit8 = new Exit(DirectionType::EAST, room2, room1, "Exit 8","Ancient Library-Entryway"); //Ancient Library-Entryway
	Exit* exit9 = new Exit(DirectionType::NORTH, room4, room1, "Exit 9", "Great Hall-Entryway"); //Great Hall-Entryway
	Exit* exit10 = new Exit(DirectionType::WEST, room5, room1,"Exit 10","Rocky Cavern-Entryway"); //Rocky Cavern-Entryway
	Exit* exit11 = new Exit(DirectionType::NORTH, room7, room2,"Exit 11","Locked Treasure-Ancient Library"); //Locked Treasure-Ancient Library
	Exit* exit12 = new Exit(DirectionType::EAST, room5, room6,"Exit 12","Rocky Cavern-Smuggler's Cove");
	Exit* exit13 = new Exit(DirectionType::WEST,room6, room5,"Exit 13","Smuggler's Cove-Rocky Cavern");

	Item* item1 = new Item("Sword", "Sword of iron from the Rocky Cavern.", EntityType::ITEM);
	room6->addContains(item1);

	player = new Player("Z1Tr0k", "First player playing zork game.", room1);

	entities.push_back(room1); entities.push_back(room2); entities.push_back(room3); entities.push_back(room4); 
	entities.push_back(room5); entities.push_back(room6); entities.push_back(room7);

	entities.push_back(exit1); entities.push_back(exit2); entities.push_back(exit3); entities.push_back(exit4); entities.push_back(exit5); entities.push_back(exit6); entities.push_back(exit7);
	entities.push_back(exit8); entities.push_back(exit9); entities.push_back(exit10); entities.push_back(exit11); entities.push_back(exit12); entities.push_back(exit13);
	
	entities.push_back(item1);

	entities.push_back(player);
}


/*
	@brief Method for reading the command entered by the player.
	@param command Vector that contains the command entered by the player.
*/
void World::processCommand(const std::vector<std::string>& command) {
	if (command.empty()) {
		return;
	}else if (command[0] == "Command" ) {
		std::cout << "\n======= AVAILABLE COMMANDS =======" << std::endl;
		std::cout << "Stats:          Shows player information." << std::endl;
		std::cout << "Go [Direction]: Moves the player towards an exit (e.g., Go North)." << std::endl;
		std::cout << "Show Room:      Displays the room description, exits, and items on the floor." << std::endl;
		std::cout << "Show Inventory: Opens your backpack to view your carried items." << std::endl;
		std::cout << "Take [Item]:    Picks up an item from the floor." << std::endl;
		std::cout << "Drop [Item]:    Drops an item to the floor." << std::endl;
		std::cout << "Exit:           Closes the game safely." << std::endl;
		std::cout << "====================================\n" << std::endl;
	}else if (command[0] == "stats") {
		player->statsPlayer();
	}else if (command[0] == "go") {
		movePlayer(command);
	}else if (command[0] == "show" && command[1] == "inventory") {
		player->showInventory();
	}else if (command[0] == "take") {
		player->takeItem(command);
	}else if (command[0] == "drop") {
		player->dropItem(command);
	}else if (command[0] == "show" && command[1] == "room") {
		player->getLocation()->showRoom();
	}
}


void World::movePlayer(const std::vector<std::string>& command) const{
	if (command.size() == 2) {
		for (const auto& it : entities) {
			if (it->getType() == EntityType::EXIT) {
				Exit* exit = dynamic_cast<Exit*>(it); //Pointer to the exit.

				if (exit->getDirectionType() == command[1]) {
					if (player->getLocation() == exit->getSource()) {
						player->setLocation(exit->getDestination());
						break;
					}
				}
			}
		}
	}
}