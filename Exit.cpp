#include "Exit.h"

/*
	@brief Default constructor of the Exit class.
*/
Exit::Exit() : direction(DirectionType::NORTH), source(nullptr), destination(nullptr){

}


/*
	@brief Parameterized constructor of the Exit class.
	@param direction Direction of the destination room.
	@param source Pointer to the current room.
	@param destination Pointer to the destination room.
*/
Exit::Exit(DirectionType direction, Room* source, Room* destination) : direction(direction), source(source), destination(destination) {

}


/*
	@brief Destroyer of the Exit class.
*/
Exit::~Exit() {

}