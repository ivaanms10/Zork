#include "Creature.h"

/*
	@brief Default constructor of the Creature class.
*/
Creature::Creature() : location(nullptr), name(""), health(100) {

}


/*
	@brief Parameterized constructor of the Creature class.
	@param name Creature name.
	@param location Room where the creature is located.
	@param health Number of lives the creature has.
*/
Creature::Creature(const std::string& name, Room* location, const int& health) : location(location), name(name), health(health) {

}


/*
	@brief Destructor of the Creature class.
*/
Creature::~Creature() {

}