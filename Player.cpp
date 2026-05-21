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


/*
    @brief Method to take an item from the room.
    @param command Vector that contains the command entered by the player.
*/
void Player::takeItem(const std::vector<std::string>& command) {
    if (command.size() == 2) {
        for (const auto& it : Creature::getLocation()->getContains()) {
            if (it->getType() == EntityType::ITEM) {
                if (it->getName() == command[1]) {
                    addContains(it);
                    Creature::getLocation()->removeContains(it);
                }
            }
        }
    }
}


/*
    @brief Method to drop an item in the room.
    @param command Vector that contains the command entered by the player.
*/
void Player::dropItem(const std::vector<std::string>& command) {
    if (command.size() == 2) {
        if (!Creature::getContains().empty()) {
            for (const auto& it : Creature::getContains()) {
                if (it->getType() == EntityType::ITEM) {
                    if (it->getName() == command[1]) {
                        Creature::getLocation()->addContains(it);
                        removeContains(it);
                    }
                }
            }
        }
    }
}