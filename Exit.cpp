#include "Exit.h"
#include "Room.h"
#include "Item.h"
#include <iostream>

/*
	@brief Default constructor of the Exit class.
*/
Exit::Exit() : Entity("","",EntityType::EXIT), direction(DirectionType::NORTH), source(nullptr), destination(nullptr), isBlocked(false), key(nullptr) {

}


/*
	@brief Parameterized constructor of the Exit class.
	@param direction Direction of the destination room.
	@param source Pointer to the current room.
	@param destination Pointer to the destination room.
	@param name Name of the exit.
	@param description Description of the exit.
	@param isBlocked True if the exit is block, False if it isn't blocked.
	@param key Item to open the blocked exit.
*/
Exit::Exit(DirectionType direction, Room* source, Room* destination, const std::string& name, const std::string& description, bool isBlocked, Item* key) : Entity(name, description, EntityType::EXIT), direction(direction), source(source), destination(destination), isBlocked(isBlocked), key(key) {

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
	switch (this->direction) {
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


/*
	@brief Method to open a close exit.
	@param item Key to open the exit.
	@return True if the exit opens correctly, False if it doesn't open correctly.
*/
bool Exit::openExit(Item* item) {
	if (item != nullptr) {
		if (key == item) {
			std::cout << "The exit is correctly open, you can go into the room ..." << std::endl;
			isBlocked = false;
			return true;
		} else {
			std::cout << "This is not the correct item to open the exit. You need " << key->getName() << std::endl;
		}
	}
	return false;
}


/*
	@brief Method to close a open exit.
	@param item Key to close the exit.
	@return True if the exit closes correctly, False if it doesn't close correctly.
*/
bool Exit::closeExit(Item* item) {
	if (item != nullptr) {
		if (!isBlocked) {
			if (key == item) {
				std::cout << "The exit is correctly close, you can't go into the room ..." << std::endl;
				isBlocked = true;
				return true;
			} else {
				std::cout << "This is not the correct item to close the exit. You need " << key->getName() << std::endl;
			}
		} else {
			std::cout << "The exit you're trying to close is already closed." << std::endl;
		}
	}
	return false;
}