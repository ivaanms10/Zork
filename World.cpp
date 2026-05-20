#include "World.h"

/*
	@brief Default constructor of the World class.
*/
World::World() {
	createWorld();
}


/*
	@brief Parameterized constructor of the World class.
	@param entities Vector that contains the entities of the world.
*/
World::World(std::vector<Entity*> entities) : entities(entities){
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

	Exit* exit1 = new Exit(DirectionType::NORTH, room1, room3); //Entryway-Sunken Garden
	Exit* exit2 = new Exit(DirectionType::SOUTH, room1, room4); //Entryway-Great  Hall
	Exit* exit3 = new Exit(DirectionType::EAST, room1, room5); //Entryway-Rocky Cavern
	Exit* exit4 = new Exit(DirectionType::WEST, room1, room2); //Entryway-Ancient Library
	Exit* exit5 = new Exit(DirectionType::WEST, room4, room7); //Great Hall-Locked Treasure
	Exit* exit6 = new Exit(DirectionType::NORTH, room6, room3); //Smuggler's Cove-Sunken Garden

	entities.push_back(room1); entities.push_back(room2); entities.push_back(room3); entities.push_back(room4); 
	entities.push_back(room5); entities.push_back(room6); entities.push_back(room7);

	entities.push_back(exit1); entities.push_back(exit2); entities.push_back(exit3); 
	entities.push_back(exit4); entities.push_back(exit5); entities.push_back(exit6);

}


/*
	@brief Method for reading the command entered by the player.
	@param command Vector that contains the command entered by the player.
*/
void World::processCommand(const std::vector<std::string>& command) {
	if (!command.empty()) {
		
	}
}