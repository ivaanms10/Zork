#include "Creature.h"

/*
	@brief Default constructor of the Creature class.
*/
Creature::Creature() : location(nullptr), name(""), health(MAX_HEALTH), shield(MAX_SHIELD) {

}


/*
	@brief Parameterized constructor of the Creature class.
	@param name Creature name.
	@param location Room where the creature is located.
	@param health Number of lives the creature has.
	@param shield Number of shield the creature has.
*/
Creature::Creature(const std::string& name, Room* location, const int& health, const int& shield) : location(location), name(name), health(health), shield(shield) {

}


/*
	@brief Destructor of the Creature class.
*/
Creature::~Creature() {

}