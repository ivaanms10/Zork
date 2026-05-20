#include "Room.h"

/*
	@brief Default constructor of the Room class.
*/
Room::Room(){

}


/*
	@brief Parameterized constructor of the Room class.
	@param name Name of the room.
	@param description Room description.
*/
Room::Room(const std::string& name, const std::string& description) : Entity(name, description) {

}


/*
	@brief Destroyer of the Room class.
*/
Room::~Room() {

}


/*

*/
void Room::Update(){
	
}