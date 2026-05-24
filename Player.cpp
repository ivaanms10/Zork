#include "Player.h"
#include "Item.h"  
#include "Room.h"  
#include "World.h"
#include "Utils.h"
#include "Exit.h"
#include <iostream>

/*
	@brief Default constructor of the Player class.
*/
Player::Player() : Creature(nullptr, "", "", EntityType::PLAYER, nullptr, MAX_HEALTH, 0), selectedItem(nullptr), numKills(0), numDeath(0), numGold(0) {
    
}


/*
	@brief Parameterized constructor of the Player class.
	@param name Player name.
	@param location Room where the player is located.
    @param world Pointer to the world where the player is located.
*/
Player::Player(const std::string& name, const std::string& description, Room* location, World* world) : Creature(world, name, description, EntityType::PLAYER, location, MAX_HEALTH, 0), selectedItem(nullptr), numKills(0), numDeath(0), numGold(0){

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
        for (const auto& it : getContains()) {
            Item* item = dynamic_cast<Item*>(it);

            if (item != nullptr) {
                std::cout << "  ->  " << item->getName() << " : " << item->getDescription() << "   " << item->getAmount() << " / " << item->getMaxAmount() << std::endl;
            }
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
    for (const auto& it : getLocation()->getContains()) {
        if (it->getType() == EntityType::ITEM) {
            Item* itemRoom = dynamic_cast<Item*>(it);
            
            if (itemRoom->getName() == Utils::getFullNameItem(command, command.size()-1)) {
                
                Item* itemInventory = existItemInventory(itemRoom);
                if (itemInventory != nullptr) {
                    int newAmount = itemInventory->getAmount() + itemRoom->getAmount();

                    if (itemInventory->getAmount() == itemInventory->getMaxAmount()) {
                        if (getContains().size() < MAX_ITEM_INVENTORY) {
                            addContains(itemRoom);
                            getLocation()->removeEntity(itemRoom);
                            std::cout << "You have put the " << itemRoom->getName() << " in your inventory." << std::endl;
                        } else {
                            std::cout << "You can't take more items because the inventory is full." << std::endl;
                        }
                    } else if (newAmount > itemInventory->getMaxAmount()) {
                        int difAmount = newAmount - itemInventory->getMaxAmount();

                        if (getContains().size() < MAX_ITEM_INVENTORY) {
                            itemInventory->setAmount(itemInventory->getMaxAmount());
                            itemRoom->setAmount(difAmount);
                            addContains(itemRoom);
                            getLocation()->removeEntity(itemRoom);
                        } else {
                            itemInventory->setAmount(itemInventory->getMaxAmount());
                            itemRoom->setAmount(difAmount);
                        }
                        std::cout << "You have put the " << itemRoom->getName() << " in your inventory." << std::endl;
                    } else {
                        std::cout << "You have put the " << itemRoom->getName() << " in your inventory." << std::endl;
                        itemInventory->setAmount(newAmount);
                        getLocation()->removeEntity(itemRoom);
                        getWorld()->removeEntity(itemRoom);
                    }   
                    break;
                } else {
                    if (getContains().size() < MAX_ITEM_INVENTORY) {
                        if (itemRoom->getItemType() != ItemType::CHEST) {
                            addContains(it);
                            getLocation()->removeEntity(it);
                            std::cout << "You have put the " << itemRoom->getName() << " in your inventory." << std::endl;
                        } else {
                            std::cout << "You can't take the chest. " << std::endl;
                        }
                    } else {
                        std::cout << "You can't take " << itemRoom->getName() << ". Your inventory is full." << std::endl;
                    }
                    break;
                }
            }
        }
    }
}


/*
    @brief Method to drop an item by its name.
    @param command Vector that contains the command entered by the player.
*/
void Player::dropItem(const std::vector<std::string>& command) {
    if (command.size() > 1) {
        try {
            int amount = std::stoi(command.back());
            
            for (const auto& it : getContains()) {
                if (it->getType() == EntityType::ITEM) {
                    if (it->getName() == Utils::getFullNameItem(command, command.size() - 2)) {
                        Item* item = dynamic_cast<Item*>(it);
                        dropItemAmount(amount, item);
                    }
                }
            }
        } catch (const std::invalid_argument& e) {
            for (const auto& it : getContains()) {
                if (it->getType() == EntityType::ITEM) {
                    if (it->getName() == Utils::getFullNameItem(command, command.size() - 1)) {
                        std::cout << it->getName() << " drop succesfully." << std::endl;
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
    @brief Method to drop the selected item.
    @param command Vector that contains the command entered by the player.
*/
void Player::dropItemSelected(const std::vector<std::string>& command) {
    if (selectedItem != nullptr) {
        if (command.size() == 2) {
            try {

                int amount = std::stoi(command[1]);
                dropItemAmount(amount, selectedItem);
                
            } catch (const std::invalid_argument& e) {
                dropItem(command);
            }
        } else {
            std::cout << selectedItem->getName() << " drop succesfully." << std::endl;
            getLocation()->addContains(selectedItem);
            removeContains(selectedItem);
            selectedItem = nullptr;
        }
    }
}


/*
    @brief Method to drop a certain amount of an item.
    @param amount Amount to be drop from the item.
    @param item Pointer to the item from which the amount will be dropped.
*/
void Player::dropItemAmount(int amount, Item* item) {
    if (amount >= item->getAmount()) {
        std::cout << item->getName() << " drop succesfully. "<<amount<<" uds." << std::endl;
        getLocation()->addContains(item);
        removeContains(item);
        item = nullptr;
    } else if (amount > 0 && amount < item->getAmount()) {
        std::cout << item->getName() << " drop succesfully. " << amount << " uds." << std::endl;
        item->setAmount(item->getAmount() - amount);
        Item* newItem = new Item(item->getName(), item->getDescription(), item->getType(), item->getItemType(), amount, item->getValue());
        getLocation()->addContains(newItem);
        getWorld()->addEntity(newItem);
    }
}


/*
    @brief Method to open a chest and drop the items from the chest into the room.
    @param command Vector that contains the command entered by the player.
*/
void Player::openChest(const std::vector<std::string>& command) {
    for (const auto& it : getLocation()->getContains()) {
        if (it != nullptr && it->getType() == EntityType::ITEM) {
            Item* chest = dynamic_cast<Item*>(it);

            if (chest != nullptr) {
                if (chest->getItemType() == ItemType::CHEST) {
                    std::cout << "==================================================" << std::endl;
                    std::cout << "               CHEST OPEN CORRECTLY               " << std::endl;
                    std::cout << "==================================================" << std::endl;
                    std::cout << " Items                                            " << std::endl;
                    std::cout << "--------------------------------------------------" << std::endl;

                    while (!chest->getContains().empty()) { // While the chest isn't empty, we continue taking items.
                        Entity* itemChest = chest->getContains().front();
                        Item* itemChest2 = dynamic_cast<Item*>(itemChest);
                        if (itemChest2 != nullptr) {
                            std::cout << "  ->  " << itemChest2->getName() << " : " << itemChest2->getDescription() << "   " << itemChest2->getAmount() << " uds. " << std::endl;
                        }
                        if (itemChest != nullptr) {
                            getLocation()->addContains(itemChest);
                            chest->removeContains(itemChest);
                        }
                    }
                    std::cout << "==================================================" << std::endl;
                    break;
                }
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

                    if (item != nullptr ){
                        if (item->getName() == Utils::getFullNameItem(command, command.size() - 1)) {
                            selectedItem = item;
                            std::cout<<"You have selected: " << item->getName() << std::endl; 
                            break;
                        }
                    }
                }
            }
        }
    }
}


/*
    @brief Method to deselect the selected item.
    @param command Vector that contains the command entered by the player.
*/
void Player::deselectItem() {
    if (selectedItem != nullptr) {
        std::cout << selectedItem->getName() << " correctly deselected..." << std::endl;
        selectedItem = nullptr;
    }
}


/*
    @brief Method to use the item selected.
    @param command Vector that contains the command entered by the player.
*/
void Player::useItemSelected() { 
        if (selectedItem != nullptr) {

            if (selectedItem->getItemType() == ItemType::BIG_SHIELD) {
                int newShield = getShield() + selectedItem->getValue();

                if (getShield() == MAX_SHIELD) {
                    std::cout << "You can't take the Big Shield. You are full shield." << std::endl;
                } else if (newShield > MAX_SHIELD) {
                    setShield(MAX_SHIELD);
                    decreaseAmountItem();
                    std::cout << "Healing with a Big Shield...." << std::endl;
                } else {
                    setShield(newShield);
                    decreaseAmountItem();
                    std::cout << "Healing with a Big Shield...." << std::endl;
                }

            } else if (selectedItem->getItemType() == ItemType::SMALL_SHIELD) {
                int newShield = getShield() + selectedItem->getValue();

                if (getShield() >= MAX_SMALL_SHIELD) {
                    std::cout << "You can't take the Small Shield." << std::endl;
                } else if (newShield > MAX_SMALL_SHIELD) {
                    setShield(MAX_SMALL_SHIELD);
                    decreaseAmountItem();
                    std::cout << "Healing with a Small Shield...." << std::endl;
                } else {
                    setShield(newShield);
                    decreaseAmountItem();
                    std::cout << "Healing with a Small Shield...." << std::endl;
                }

            } else if (selectedItem->getItemType() == ItemType::KIT) {
                
                if (getHealth() == MAX_HEALTH) {
                    std::cout << "You can't take the Kit." << std::endl;
                } else {
                    setHealth(MAX_HEALTH);
                    decreaseAmountItem();
                    std::cout << "Healing with a Kit...." << std::endl;
                }

            } else if (selectedItem->getItemType() == ItemType::BANDAGES) {
                int newHealth = getHealth() + selectedItem->getValue();

                if (getHealth() >= MAX_BANDAGES_HEALTH) {
                    std::cout << "You can't take the Bandages." << std::endl;
                } else if (newHealth > MAX_BANDAGES_HEALTH) {
                    setHealth(MAX_BANDAGES_HEALTH);
                    decreaseAmountItem();
                    std::cout << "Healing with Bandages...." << std::endl;
                } else {
                    setHealth(newHealth);
                    decreaseAmountItem();
                    std::cout << "Healing with Bandages...." << std::endl;
                }
            }

        } else {
            std::cout << "You don't have items selected to use." << std::endl;
        }
    }


/*
    @brief Method to reduce the amount of an item, if the amount reaches 0, we remove the item.
*/
void Player::decreaseAmountItem() {
    if (selectedItem != nullptr) {
        selectedItem->decreaseAmount();
        if (selectedItem->getAmount() == 0) {
            removeContains(selectedItem);
            getWorld()->removeEntity(selectedItem);
            selectedItem = nullptr;
        }
    }
}


/*
    @brief Method to determine if an item is already in the inventory or not.
    @param item Item we are looking for in the inventory.
    return True if the item is already in the inventory, or false if the item isn't in the inventory.
*/
Item* Player::existItemInventory(Item* item) {
    if (item != nullptr) {
        for (const auto& it : getContains()) {
            if (it->getName() == item->getName()) {
                Item* item = dynamic_cast<Item*>(it);
                return item;
            }
        }
    }
    return nullptr;
}


/*
    @brief Method to open a close exit.
    @param command Vector that contains the command entered by the player.
*/
void Player::openExit(const std::vector<std::string>& command) {
    if (command.size() == 2) {
        if (selectedItem != nullptr) {
            for (const auto& it : getLocation()->getContains()) {
                if (it->getType() == EntityType::EXIT) {
                    Exit* exit = dynamic_cast<Exit*>(it); //Pointer to the exit.

                    if (exit->getDirectionType() == command[1]) {
                        if (exit->getBlocked()) {
                            exit->openExit(selectedItem);
                        }
                        std::cout << "The exit is correctly open, you can go into the room ..." << std::endl;
                        break;
                    }
                }
            }
        } else {
            std::cout << "You need to have the correct object selected to open the door." << std::endl;
        }
    }
}


/*
    @brief Method to close a open exit.
    @param command Vector that contains the command entered by the player.
*/
void Player::closeExit(const std::vector<std::string>& command) {
    if (command.size() == 2) {
        if (selectedItem != nullptr) {
            for (const auto& it : getLocation()->getContains()) {
                if (it->getType() == EntityType::EXIT) {
                    Exit* exit = dynamic_cast<Exit*>(it); //Pointer to the exit.

                    if (exit->getDirectionType() == command[1]) {
                        if (!exit->getBlocked()) {
                            exit->closeExit(selectedItem);
                        } 
                        std::cout << "The exit is correctly close ..." << std::endl;
                        break;
                    }
                }
            }
        } else {
            std::cout << "You need to have the correct object selected to open the door." << std::endl;
        }
    }
}


/*
    @brief Method to move the player around the map.
    @param command Vector that contains the command entered by the player.
*/
void Player::movePlayer(const std::vector<std::string>& command) {
    if (command.size() == 2) {
        for (const auto& it : getLocation()->getContains()) {
            if (it->getType() == EntityType::EXIT) {
                Exit* exit = dynamic_cast<Exit*>(it); //Pointer to the exit.

                if (exit->getDirectionType() == command[1]) {
                    if (exit->getBlocked()) {
                        std::cout << "The exit is blocked. You need " << exit->getKey()->getName() << " to open." << std::endl;
                    } else {
                        setLocation(exit->getDestination());
                        std::cout << "You've moved to the room " << exit->getDestination()->getName() << std::endl;
                    }
                    break;
                }
            }
        }
    }
}


/*
    @brief
*/
void Player::autoTake() {
    std::list<Entity*> addItemsInventory;

    for (const auto& it : getLocation()->getContains()) {
        Item* item = dynamic_cast<Item*>(it);
        if (item->getItemType() == ItemType::GOLD) {
            addItemsInventory.push_back(item);
        } else if (item->getItemType() == ItemType::AMMUNITION) {
            addItemsInventory.push_back(item);
        }
    }

    for (const auto& it : addItemsInventory) {
        Item* item = dynamic_cast<Item*>(it);
        if (item->getItemType() == ItemType::GOLD) {
            int newGold = numGold + item->getAmount();

            if (newGold > MAX_GOLD) {
                int difGold = newGold - MAX_GOLD;

                std::cout << " + " << MAX_GOLD - numGold << " gold." << std::endl;
                setGold(MAX_GOLD);
                item->setAmount(difGold);
            } else {
                setGold(newGold);
                std::cout << " + " << item->getAmount() << " gold." << std::endl;
                getLocation()->removeEntity(it);
                getWorld()->removeEntity(it);
            }
  
        } else if (item->getItemType() == ItemType::AMMUNITION) {
            int newAmmo = numAmmo + item->getAmount();

            if (newAmmo > MAX_AMMUNATION) {
                int difAmmo = newAmmo - MAX_AMMUNATION;

                std::cout << " + " << MAX_AMMUNATION - numAmmo << " ammo." << std::endl;
                setAmmo(MAX_AMMUNATION);
                item->setAmount(difAmmo);
            } else {
                setAmmo(newAmmo);
                std::cout << " + " << item->getAmount() << " ammo." << std::endl;
                getLocation()->removeEntity(it);
                getWorld()->removeEntity(it);
            }

        }
    }
}