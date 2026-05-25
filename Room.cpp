#include "Room.h"
#include "Item.h"
#include "Exit.h"
#include <iostream>

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
    @brief Method to show the room items.
*/
void Room::showRoom() const {
    std::cout << "==================================================" << std::endl;
    std::cout << "                     ROOM                         " << std::endl;
    std::cout << "==================================================" << std::endl;
	std::cout << " Name: " << Entity::getName() << "                " << std::endl;
	std::cout << " Description: " << Entity::getDescription() << "  " << std::endl;
	std::cout << "--------------------------------------------------" << std::endl << std::endl;

	std::list<Item*> itemRoom;
	for (const auto& it : getContains()) {
		Item* item = dynamic_cast<Item*>(it);

		if (item != nullptr) {
			itemRoom.push_back(item);
		}
	}

	if (itemRoom.empty()) {
		std::cout << "               The room is empty.              " << std::endl << std::endl;
	}else {
		for (const auto& it : itemRoom) {
			std::cout << "  ->  " << it->getName() << " : " << it->getDescription() << "   " << it->getAmount() << " / " << it->getMaxAmount() << std::endl;
		}
	}
    std::cout << "==================================================" << std::endl;
}


/*
	@brief Method to show the room exits.
*/
void Room::showExits() const {
	std::cout << "==================================================" << std::endl;
	std::cout << "                     ROOM                         " << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << " Name: " << Entity::getName() << "                " << std::endl;
	std::cout << " Description: " << Entity::getDescription() << "  " << std::endl;
	std::cout << "--------------------------------------------------" << std::endl << std::endl;

	std::list<Exit*> exitsRoom;
	for (const auto& it : getContains()) {
		Exit* exit = dynamic_cast<Exit*>(it);

		if (exit != nullptr) {
			exitsRoom.push_back(exit);
		}
	}

	if (exitsRoom.empty()) {
		std::cout << "               The room has no exits.              " << std::endl << std::endl;
	} else {
		for (const auto& it : exitsRoom) {
			std::cout << "  ->  " << it->getDirectionType() << " : Source -> " << it->getSource()->getName() << "  Destination -> " << it->getDestination()->getName() << std::endl;
		}
	}
	std::cout << "==================================================" << std::endl;
}