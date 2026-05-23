#include "Creature.h"
#include "Room.h"
#include "World.h"

/*
	@brief Default constructor of the Creature class.
*/
Creature::Creature() : Entity("","",EntityType::CREATURE), world(nullptr), location(nullptr), health(MAX_HEALTH), shield(MAX_SHIELD) {

}


/*
	@brief Parameterized constructor of the Creature class.
	@param world Pointer to the world.
	@param name Creature name.
	@param description Creature description.
	@param type Type of the creature.
	@param location Room where the creature is located.
	@param health Number of lives the creature has.
	@param shield Number of shield the creature has.
*/
Creature::Creature(World* world, const std::string& name, const std::string& description, EntityType type, Room* location, int health, int shield) : Entity(name, description, type), world(world), location(location), health(health), shield(shield) {

}


/*
	@brief Destructor of the Creature class.
*/
Creature::~Creature() {

}