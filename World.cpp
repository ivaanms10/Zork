#include "World.h"
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "NPC.h"
#include <random>
#include <algorithm>
#include <iostream>

/*
	@brief Default constructor of the World class.
*/
World::World() : player(nullptr){
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


	Item* item1 = new Item("Big Chest", "Chest that contains a weapon and a curative item", EntityType::ITEM, ItemType::CHEST, 1, 1, 0);
	Item* item2 = new Item("M4", "Rifle to kill enemies", EntityType::ITEM, ItemType::RIFLE, 1, 25, PRICE_RIFLE);
	Item* item3 = new Item("Big Shield", "Shield that health 50", EntityType::ITEM, ItemType::BIG_SHIELD, 1, 50, PRICE_BIG_SHIELD);
	Item* item4 = new Item("Small Shield", "Shield that health 25", EntityType::ITEM, ItemType::SMALL_SHIELD, 3, 25, PRICE_SMALL_SHIELD);
	Item* item5 = new Item("Small Shield", "Shield that health 25", EntityType::ITEM, ItemType::SMALL_SHIELD, 3, 25, PRICE_SMALL_SHIELD);
	Item* item6 = new Item("Small Shield", "Shield that health 25", EntityType::ITEM, ItemType::SMALL_SHIELD, 3, 25, PRICE_SMALL_SHIELD);
	Item* item7 = new Item("Magic Key", "Key to open blocked exits", EntityType::ITEM, ItemType::KEY, 1, 1, 0);


	Exit* exit1 = new Exit(DirectionType::NORTH, room1, room3,"Exit 1", "Entryway-Sunken Garden", false,nullptr); 
	Exit* exit2 = new Exit(DirectionType::SOUTH, room1, room4, "Exit 2", "Entryway-Great Hall", false, nullptr);
	Exit* exit3 = new Exit(DirectionType::EAST, room1, room5, "Exit 3", "Entryway-Rocky Cavern", false, nullptr);
	Exit* exit4 = new Exit(DirectionType::WEST, room1, room2, "Exit 4", "Entryway-Ancient Library", false, nullptr);
	Exit* exit5 = new Exit(DirectionType::WEST, room4, room7, "Exit 5", "Great Hall-Locked Treasure", true, item7);
	Exit* exit6 = new Exit(DirectionType::NORTH, room6, room3, "Exit 6", "Smuggler's Cove-Sunken Garden", false, nullptr);
	Exit* exit7 = new Exit(DirectionType::SOUTH, room3, room1, "Exit 7", "Sunken Garden-Entryway", false, nullptr);
	Exit* exit8 = new Exit(DirectionType::EAST, room2, room1, "Exit 8","Ancient Library-Entryway", false, nullptr);
	Exit* exit9 = new Exit(DirectionType::NORTH, room4, room1, "Exit 9", "Great Hall-Entryway", false, nullptr);
	Exit* exit10 = new Exit(DirectionType::WEST, room5, room1,"Exit 10","Rocky Cavern-Entryway", false, nullptr);
	Exit* exit11 = new Exit(DirectionType::NORTH, room7, room2,"Exit 11","Locked Treasure-Ancient Library", true, item7); 
	Exit* exit12 = new Exit(DirectionType::EAST, room5, room6,"Exit 12","Rocky Cavern-Smuggler's Cove", false, nullptr);
	Exit* exit13 = new Exit(DirectionType::WEST,room6, room5,"Exit 13","Smuggler's Cove-Rocky Cavern", false, nullptr);
	

	NPC* npc1 = new NPC("Seller", "Item seller", NPCType::SELLER, room1, this);

	player = new Player("Ivan", "First player playing zork game.", room1, this);

	room1->addContains(exit1); room1->addContains(exit2); room1->addContains(exit3); room1->addContains(exit4);
	room2->addContains(exit8);
	room3->addContains(exit7);
	room4->addContains(exit9); room4->addContains(exit5);
	room5->addContains(exit10); room5->addContains(exit12);
	room6->addContains(exit6);room6->addContains(exit13);
	room7->addContains(exit11);

	item1->addContains(item2); item1->addContains(item3); item1->addContains(item7);
	room4->addContains(item4); room3->addContains(item1); room1->addContains(item5); room3->addContains(item6); room1->addContains(npc1);
	

	entities.push_back(room1); entities.push_back(room2); entities.push_back(room3); entities.push_back(room4); 
	entities.push_back(room5); entities.push_back(room6); entities.push_back(room7);
	
	entities.push_back(exit1); entities.push_back(exit2); entities.push_back(exit3); entities.push_back(exit4); entities.push_back(exit5); entities.push_back(exit6); entities.push_back(exit7);
	entities.push_back(exit8); entities.push_back(exit9); entities.push_back(exit10); entities.push_back(exit11); entities.push_back(exit12); entities.push_back(exit13);
	
	entities.push_back(item1); 	entities.push_back(item2); 	entities.push_back(item3); 	entities.push_back(item4); entities.push_back(item5); entities.push_back(item6); entities.push_back(item7);

	entities.push_back(npc1);

	entities.push_back(player);
}


/*
	@brief Method for reading the command entered by the player.
	@param command Vector that contains the command entered by the player.
*/
void World::processCommand(const std::vector<std::string>& command) {
	if (command.empty()) {
		return;
	}else if (command[0] == "command" ) {
		std::cout << "\n======= AVAILABLE COMMANDS =======" << std::endl;
		std::cout << "stats:          Shows player information." << std::endl;
		std::cout << "go [Direction]: Moves the player towards an exit (e.g., Go North)." << std::endl;
		std::cout << "show room:      Displays the room description, exits, and items on the floor." << std::endl;
		std::cout << "show inventory: Opens your backpack to view your carried items." << std::endl;
		std::cout << "take [Item]:    Picks up an item from the floor." << std::endl;
		std::cout << "drop: Drops the item selected to the floor." << std::endl;
		std::cout << "use: Use the selected item." << std::endl;
		std::cout << "Exit:           Closes the game safely." << std::endl;
		std::cout << "====================================\n" << std::endl;
	}else if (command[0] == "stats") {
		player->statsPlayer();
	}else if (command[0] == "go") {
		player->movePlayer(command);
	}else if (command[0] == "show" && command[1] == "inventory") {
		player->showInventory();
	}else if (command[0] == "take") {
		player->takeItem(command);
	}else if (command.size() > 2 && command[0] == "drop") {
		player->dropItem(command);
	}else if (command[0] == "show" && command[1] == "room") {
		player->getLocation()->showRoom();
	}else if (command[0] == "open" && command[1] == "chest") {
		player->openChest(command);
	}else if (command[0] == "select") {
		player->selectItem(command);
	}else if (command[0] == "use") {
		player->useItemHealer();
	}else if (command[0] == "drop") {
		player->dropItemSelected(command);
	} else if (command[0] == "open") {
		player->openExit(command);
	} else if (command[0] == "close") {
		player->closeExit(command);
	} else if (command[0] == "show" && command[1] == "exits") {
		player->getLocation()->showExits();
	}else if (command[0] == "deselect") {
		player->deselectItem();
	}else if (command[0] == "talk") {
		player->talkNPC();
	}else if (command[0] == "view" && command[1] == "shop") {
		player->viewShop();
	}else if (command[0] == "radar") {
		player->viewRadar();
	}
}


/*
	@brief Method to remove and delete an entity from the world.
	@param entity Entity that will be deleted.
*/
void World::removeEntity(Entity* entity) {
	if (entity != nullptr) {
		entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
		delete entity;
	}
}