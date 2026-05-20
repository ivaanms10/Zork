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