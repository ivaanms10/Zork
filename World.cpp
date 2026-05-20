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
	entities.clear();
}


/*
	@brief Method to create a world with its respective entities.
*/
void World::createWorld() {

}


/*
	@brief Method for reading the command entered by the player.
	@param command Vector that contains the command entered by the player.
*/
void World::processCommand(const std::vector<std::string>& command) {

}