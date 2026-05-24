#include "NPC.h"
#include "Room.h"  
#include "World.h"
#include "Item.h"
#include <iostream>

/*
	@brief Default constructor of the NPC class.
*/
NPC::NPC() : Creature(nullptr, "", "", EntityType::NPC, nullptr, MAX_HEALTH, MAX_SHIELD, MAX_GOLD_CREATURE), type(NPCType::ENEMIES) {

}


/*
	@brief Parameterized constructor of the NPC class.
	@param name NPC name.
	@param description NPC description.
	@param type Type of NPC.
	@param location Room where the NPC is located.
	@param world Pointer to the world where the NPC is located.
*/
NPC::NPC(const std::string& name, const std::string& description, NPCType type, Room* location, World* world) : Creature(world, name, description, EntityType::NPC, location, MAX_HEALTH, MAX_SHIELD, MAX_GOLD_CREATURE), type(type) {

}


/*
	@brief Destructor of the NPC class.
*/
NPC::~NPC() {

}


/*
	@brief Method to show the room items.
*/
void NPC::showShop() const {
	if (type == NPCType::SELLER) {
		std::cout << "==================================================" << std::endl;
		std::cout << "                       SHOP                       " << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << " Items                                            " << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;

		std::list<Item*> itemShop;
		for (const auto& it : getContains()) {
			Item* item = dynamic_cast<Item*>(it);

			if (item != nullptr) {
				itemShop.push_back(item);
			}
		}

		if (itemShop.empty()) {
			std::cout << "               The shop is empty.              " << std::endl << std::endl;
		} else {
			for (const auto& it : itemShop) {
				std::cout << "  ->  " << it->getName() << " : " << it->getDescription() << "   " << it->getAmount() << " / " << it->getMaxAmount() <<"   Price: "<<it->getPrice()<< std::endl;
			}
		}
		std::cout << "==================================================" << std::endl;
	}
}


/*
	@brief
*/
Item* NPC::buyItem(const std::string& itemName, int goldPlayer) {
	for (const auto& it : getContains()) {
		Item* item = dynamic_cast<Item*>(it);

		if (item != nullptr) {
			if (item->getName() == itemName) {
				if (goldPlayer >= item->getPrice()) {
					removeContains(item);
					return item;
				} else {
					std::cout << "You don't have enough gold to buy " << item->getName() << ". It costs " << item->getPrice() << " gold." << std::endl;
				}
			} else {
				std::cout << "There are no " << itemName << " currently available in the shop." << std::endl;
			}
		}
	}
	return nullptr;
}


/*
	@brief
*/
bool NPC::sellItem(Item* item) {
	if (item != nullptr) {
		if (item->getPrice() < getGold()) {
			addContains(item);
			return true;
		} else {
			std::cout << "You can't sell the" << item->getName() << ". " << getName() << " doesn't have enough gold to buy it." << std::endl;
		}
	}
	return false;
}