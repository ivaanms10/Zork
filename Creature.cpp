#include "Creature.h"

/*
	@brief Default constructor of the Creature class.
*/
Creature::Creature() : location(nullptr), name("") {

}


/*
	@brief Parameterized constructor of the Creature class.
	@param location Room where the creature is located.
	@param name Creature name.
*/
Creature::Creature(Room* location, const std::string& name) : location(location), name(name) {

}


/*
	@brief Destructor of the Creature class.
*/
Creature::~Creature() {

}