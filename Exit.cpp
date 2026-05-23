#include "Exit.h"
#include "Room.h"

/*
	@brief Default constructor of the Exit class.
*/
Exit::Exit() : Entity("","",EntityType::EXIT), direction(DirectionType::NORTH), source(nullptr), destination(nullptr) {

}


/*
	@brief Parameterized constructor of the Exit class.
	@param direction Direction of the destination room.
	@param source Pointer to the current room.
	@param destination Pointer to the destination room.
	@param name Name of the exit.
	@param description Description of the exit.
*/
Exit::Exit(DirectionType direction, Room* source, Room* destination, const std::string& name, const std::string& description) : Entity(name, description, EntityType::EXIT), direction(direction), source(source), destination(destination) {

}


/*
	@brief Destroyer of the Exit class.
*/
Exit::~Exit() {

}

/*
	@brief Method to pass the enum of DirectionType to string.
	@return String with the direction.
*/
std::string Exit::getDirectionType() const{
	switch (direction) {
		case DirectionType::NORTH:
			return "North";

		case DirectionType::SOUTH:
			return "South";

		case DirectionType::EAST:
			return "East";

		case DirectionType::WEST:
			return "West";
	}
}