#include "Room.h"

/*
	@brief Default constructor of the Room class.
*/
Room::Room() : Entity("","",EntityType::ROOM) {

}


/*
	@brief Parameterized constructor of the Room class.
	@param name Name of the room.
	@param description Room description.
*/
Room::Room(const std::string& name, const std::string& description) : Entity(name, description, EntityType::ROOM) {

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


/*
    @brief Method to show the room items.
*/
void Room::showRoom() const {
    std::cout << "==================================================" << std::endl;
    std::cout << "                     ROOM                         " << std::endl;
    std::cout << "==================================================" << std::endl;
	std::cout << " Name: " << Entity::getName() << "                " << std::endl;
	std::cout << " Description: " << Entity::getDescription() << "  " << std::endl;
	std::cout << "--------------------------------------------------" << std::endl << std::endl;
	if (Entity::getContains().empty()) {
		std::cout << "               The room is empty.              " << std::endl << std::endl;
	}else {
		int i = 1;
		for (const auto& it : Entity::getContains()) {
			std::cout << "  " << i << "   " << it->getName() << " : " << it->getDescription() << "     " << std::endl;
		}
	}
    std::cout << "==================================================" << std::endl;
}