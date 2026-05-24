#include "NPC.h"
#include "Room.h"  
#include "World.h"

/*
	@brief Default constructor of the NPC class.
*/
NPC::NPC() : Creature(nullptr, "", "", EntityType::NPC, nullptr, MAX_HEALTH, MAX_SHIELD) {

}


/*
	@brief Parameterized constructor of the NPC class.
	@param name NPC name.
	@param location Room where the NPC is located.
	@param world Pointer to the world where the NPC is located.
*/
NPC::NPC(const std::string& name, const std::string& description, Room* location, World* world) : Creature(world, name, description, EntityType::NPC, location, MAX_HEALTH, MAX_SHIELD) {

}


/*
	@brief Destructor of the NPC class.
*/
NPC::~NPC() {

}