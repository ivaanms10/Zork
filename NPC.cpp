#include "NPC.h"
#include "Room.h"  
#include "World.h"
#include "Item.h"
#include "Player.h"
#include "Exit.h"
#include <iostream>
#include <vector>

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
	@brief Method to buy a new item from the NPC seller.
	@param itemName Name of the item the player wants to buy.
	@param goldPlayer Amount of gold the player has.
	@return Pointer to the new item or nullptr if you cant buy the item.
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
	@brief Method to sell an item to the NPC seller.
	@param item Pointer to the item you are going to sell to the NPC seller.
	@return True if you sell the item succesfully, False if you don't sell it.
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


/*
	@brief Method to cause damage to the main player.
*/
void NPC::attackPlayer() {
	if (type == NPCType::ENEMIES) {
		int damage = (rand() % MAX_DAMAGE_ENEMIE) + MIN_DAMAGE_ENEMIE;
		Player* player = getWorld()->getPlayer();

		if (player != nullptr) {
			player->receiveDamage(damage);
			std::cout << " ->" << player->getName() << "   Health: " << player->getHealth() << "  Shield: " << player->getShield() << std::endl;
		}
	}
}


/*
	@brief Method to update the movement of the NPC.
*/
void NPC::Update() {
	Player* player = getWorld()->getPlayer();

	if (player != nullptr) {
		if (getLocation() != player->getLocation()) {
			std::vector<Room*> allRoomsToMove;
			for (const auto& it : getLocation()->getContains()) {
				Exit* exit = dynamic_cast<Exit*>(it);

				if (exit != nullptr) {
					if (!exit->getBlocked()) {
						allRoomsToMove.push_back(exit->getDestination());
					}
				}
			}

			if (!allRoomsToMove.empty()) {
				Room* newDestination = allRoomsToMove[rand() % allRoomsToMove.size()];
				getLocation()->removeEntity(this);
				newDestination->addEntity(this);
				setLocation(newDestination);
			}
		}
	}
}