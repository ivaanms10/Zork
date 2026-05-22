#include "Player.h"

/*
	@brief Default constructor of the Player class.
*/
Player::Player() : Creature("", "", EntityType::PLAYER, nullptr, MAX_HEALTH, 0), selectedItem(nullptr), numKills(0), numDeath(0), numGold(0) {
    
}


/*
	@brief Parameterized constructor of the Player class.
	@param name Player name.
	@param location Room where the player is located.
*/
Player::Player(const std::string& name, const std::string& description, Room* location) : Creature(name, description, EntityType::PLAYER, location, MAX_HEALTH, 0), selectedItem(nullptr), numKills(0), numDeath(0), numGold(0){

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
    std::cout << " Nick: " << getName() << "              " << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    std::cout << " HEALTH:  " << getHealth() << " / 100"    << std::endl;
    std::cout << " SHIELD: " << getShield() << " / 100"     << std::endl;

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
    std::cout << "                     INVENTORY            "<<getContains().size()<<"/"<<MAX_ITEM_INVENTORY<<"              " << std::endl;
    std::cout << "==================================================" << std::endl << std::endl;
    if (getContains().empty()) {
        std::cout << "               The inventory is empty.              " << std::endl << std::endl;
    } else {
        int i = 1;
        for (const auto& it : getContains()) {
            Item* item = dynamic_cast<Item*>(it);
            std::cout << "  ->  " << item->getName() << " : " << item->getDescription() << "   "<<item->getAmount()<<"  " << std::endl;
        }

        if (selectedItem != nullptr) {
            std::cout << "--------------------------------------------------" << std::endl;
            std::cout << " ---> Item Selected: " << selectedItem->getName()  << std::endl;
        }
    }
    std::cout << "==================================================" << std::endl;
}


/*
    @brief Method to take an item from the room.
    @param command Vector that contains the command entered by the player.
*/
void Player::takeItem(const std::vector<std::string>& command) {
    if (command.size() > 1) {
        for (const auto& it : getLocation()->getContains()) {
            if (it->getType() == EntityType::ITEM) {
                Item* item = dynamic_cast<Item*>(it);
                if (it->getName() == Utils::getFullNameItem(command)) {
                    if (item->getItemType() != ItemType::CHEST) {
                        addContains(it);
                        getLocation()->removeContains(it);
                        break;
                    } else {
                        std::cout << "You can't take the chest. " << std::endl;
                        break;
                    }
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
    if (command.size() > 1) {
        if (!getContains().empty()) {
            for (const auto& it : getContains()) {
                if (it->getType() == EntityType::ITEM) {
                    if (it->getName() == Utils::getFullNameItem(command)) {
                        getLocation()->addContains(it);
                        removeContains(it);
                        break;
                    }
                }
            }
        }
    }
}


/*
    @brief Method to open a chest and drop the items from the chest into the room.
    @param command Vector that contains the command entered by the player.
*/
void Player::openChest(const std::vector<std::string>& command) {
    for (const auto& it : getLocation()->getContains()) {
        if (it->getType() == EntityType::ITEM) {
            Item* item = dynamic_cast<Item*>(it);

            if (item->getItemType() == ItemType::CHEST) {
                for (const auto& iterator : item->getContains()) {
                    getLocation()->addContains(iterator);
                    item->removeContains(iterator);
                }
                break;
            }
        }
    }
}


/*
    @brief Method to select an item from the inventory.
    @param command Vector that contains the command entered by the player.
*/
void Player::selectItem(const std::vector<std::string>& command) {
    if (command.size() > 1) {
        if (getContains().size() > 0) {
            for (const auto& it : getContains()) {
                if (it->getType() == EntityType::ITEM) {
                    Item* item = dynamic_cast<Item*>(it);

                    if (item->getName() == Utils::getFullNameItem(command)) {
                        selectedItem = item;
                        break;
                    }
                }
            }
        }
    }
}


void Player::useItem(const std::vector<std::string>& command) {
    if (command.size() > 1) {
        if (selectedItem != nullptr) {
            if (selectedItem->getName() == Utils::getFullNameItem(command)) {
                if (selectedItem->getItemType() == ItemType::BIG_SHIELD) {
                    int newShield = getShield() + selectedItem->getValue();

                    if (getShield() == MAX_SHIELD) {
                        std::cout << "You can't take the Big Shield." << std::endl;
                    } else if (newShield > MAX_SHIELD) {
                        setShield(MAX_SHIELD);
                        decreaseAmountItem();
                    } else {
                        setShield(newShield);
                        decreaseAmountItem();
                    }

                } else if (selectedItem->getItemType() == ItemType::SMALL_SHIELD) {
                    int newShield = getShield() + selectedItem->getValue();

                    if (getShield() >= MAX_SMALL_SHIELD) {
                        std::cout << "You can't take the Small Shield." << std::endl;
                    } else if(newShield > MAX_SMALL_SHIELD) {
                        setShield(MAX_SMALL_SHIELD);
                        decreaseAmountItem();
                    } else {
                        setShield(newShield);
                        decreaseAmountItem();
                    }

                } else if (selectedItem->getItemType() == ItemType::KIT) {
                    int newHealth = getHealth() + selectedItem->getValue();

                    if (getHealth() == MAX_HEALTH) {
                        std::cout << "You can't take the Kit." << std::endl;
                    } else if (newHealth > MAX_HEALTH) {
                        setShield(MAX_HEALTH);
                        decreaseAmountItem();
                    }

                } else if (selectedItem->getItemType() == ItemType::BANDAGES) {
                    int newHealth = getHealth() + selectedItem->getValue();

                    if (getHealth() >= MAX_BANDAGES_HEALTH) {
                        std::cout << "You can't take the Bandages." << std::endl;
                    } else if (newHealth > MAX_BANDAGES_HEALTH) {
                        setShield(MAX_BANDAGES_HEALTH);
                        decreaseAmountItem();
                    } else {
                        setShield(newHealth);
                        decreaseAmountItem();
                    }
                }
            }
        } else {
            std::cout << "You don't have items selected to use." << std::endl;
        }
    }
}


/*
    @brief Method to reduce the amount of an item, if the amount reaches 0, we remove the item.
*/
void Player::decreaseAmountItem() {
    selectedItem->decreaseAmount();
    if (selectedItem->getAmount() == 0) {
        removeContains(selectedItem);
        selectedItem = nullptr;
    }
}