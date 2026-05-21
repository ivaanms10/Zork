#include "Player.h"

/*
	@brief Default constructor of the Player class.
*/
Player::Player() : Creature("", "", EntityType::PLAYER, nullptr, MAX_HEALTH, 0), numKills(0), numDeath(0), numGold(0) {
    
}


/*
	@brief Parameterized constructor of the Player class.
	@param name Player name.
	@param location Room where the player is located.
*/
Player::Player(const std::string& name, const std::string& description, Room* location) : Creature(name, description, EntityType::PLAYER, location, MAX_HEALTH, 0), numKills(0), numDeath(0), numGold(0){

}


/*
	@brief Destructor of the Player class.
*/
Player::~Player(){
    
}

/*
    @brief Method to show in the screen the player stats.
*/
void Player::statsPlayer() const{
    std::cout << "==================================================" << std::endl;
    std::cout << "                 PLAYER PROFILE                " << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << " Nick: " << Creature::getName() << "              " << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    std::cout << " HEALTH:  " << Creature::getHealth() << " / 100"    << std::endl;
    std::cout << " SHIELD: " << Creature::getShield() << " / 100"     << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " Kills:   " << numKills << "                 Death: " << numDeath << std::endl;
    std::cout << " Gold:  " << numGold << std::endl;
    std::cout << "==================================================" << std::endl;
}


/*
    @brief Method to add an item to the player inventory.
    @item item Item to be added to the inventory
*/
void Player::takeItem(Item* item) {
    if (item != nullptr) {
        if (Entity::getContains().size() <= MAX_ITEM_INVENTORY) {
            Entity::addContains(item);
        }
    }
}


/*
    @brief Method to show the player items.
*/
void Player::showInventory() const {
    std::cout << "==================================================" << std::endl;
    std::cout << "                     INVENTORY            "<<Entity::getContains().size()<<"/"<<MAX_ITEM_INVENTORY<<"              " << std::endl;
    std::cout << "==================================================" << std::endl;
    int i = 1;
    for (const auto& it : Entity::getContains()) {
        std::cout << "  " << i << "   " << it->getName() << " : " << it->getDescription()<<"     " << std::endl;
    }
    std::cout << "==================================================" << std::endl;
}