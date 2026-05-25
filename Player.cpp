#include "Player.h"
#include "Item.h"  
#include "Room.h"  
#include "World.h"
#include "Utils.h"
#include "Exit.h"
#include "NPC.h"
#include <iostream>

/*
	@brief Default constructor of the Player class.
*/
Player::Player() : Creature(nullptr, "", "", EntityType::PLAYER, nullptr, MAX_HEALTH, 0, 0), selectedItem(nullptr), selectedNPC(nullptr), numKills(0), numDeath(0), numAmmo(0) {
    
}


/*
	@brief Parameterized constructor of the Player class.
	@param name Player name.
    @param description Player description.
	@param location Room where the player is located.
    @param world Pointer to the world where the player is located.
*/
Player::Player(const std::string& name, const std::string& description, Room* location, World* world) : Creature(world, name, description, EntityType::PLAYER, location, MAX_HEALTH, 0, 0), selectedItem(nullptr), selectedNPC(nullptr), numKills(0), numDeath(0), numAmmo(0){

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
    std::cout << " Gold:  " << getGold() << "                  Ammo: " << numAmmo << std::endl;
    std::cout << "==================================================" << std::endl;
}


/*
    @brief Method to show the player items.
*/
void Player::showInventory() const {
    std::cout << "==================================================" << std::endl;
    std::cout << "                     INVENTORY            "<<getContains().size()<<"/"<<MAX_ITEM_INVENTORY<<"              " << std::endl;
    std::cout << "==================================================" << std::endl << std::endl;

    std::list<Item*> itemsInventory;
    for (const auto& it : getContains()) {
        Item* item = dynamic_cast<Item*>(it);

        if (item != nullptr) {
            itemsInventory.push_back(item);
        }
    }

    if (itemsInventory.empty()) {
        std::cout << "               The inventory is empty.              " << std::endl << std::endl;
    } else {
        for (const auto& it : itemsInventory) {
            std::cout << "  ->  " << it->getName() << " : " << it->getDescription() << "   " << it->getAmount() << " / " << it->getMaxAmount() << std::endl;
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
        Item* itemRoom = dynamic_cast<Item*>(it);

        if (itemRoom != nullptr) {
            if (itemRoom->getName() == Utils::getFullNameItem(command, command.size() - 1)) {

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
                            addContains(itemRoom);
                            getLocation()->removeEntity(itemRoom);
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
    try {
        int amount = std::stoi(command.back());

        for (const auto& it : getContains()) {
            Item* item = dynamic_cast<Item*>(it);

            if (item != nullptr) {
                if (it->getName() == Utils::getFullNameItem(command, command.size() - 2)) {
                    dropItemAmount(amount, item);
                }
            }
        }
    }
    catch (const std::invalid_argument&) {
        for (const auto& it : getContains()) {
            Item* item = dynamic_cast<Item*>(it);

            if (item != nullptr) {
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


/*
    @brief Method to drop the selected item.
    @param command Vector that contains the command entered by the player.
*/
void Player::dropItemSelected(const std::vector<std::string>& command) {
    if (selectedItem != nullptr) {
        std::cout << selectedItem->getName() << " drop succesfully." << std::endl;
        getLocation()->addContains(selectedItem);
        removeContains(selectedItem);
        selectedItem = nullptr;
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
    } else if (amount > 0 && amount < item->getAmount()) {
        std::cout << item->getName() << " drop succesfully. " << amount << " uds." << std::endl;
        item->setAmount(item->getAmount() - amount);
        Item* newItem = new Item(item->getName(), item->getDescription(), item->getType(), item->getItemType(), amount, item->getValue(), item->getPrice());
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
        Item* chest = dynamic_cast<Item*>(it);

        if (chest != nullptr) {
            if (chest->getItemType() == ItemType::CHEST) {
                std::cout << "==================================================" << std::endl;
                std::cout << "               CHEST OPEN CORRECTLY               " << std::endl;
                std::cout << "==================================================" << std::endl;
                std::cout << " Items                                            " << std::endl;
                std::cout << "--------------------------------------------------" << std::endl;

                while (!chest->getContains().empty()) { // While the chest isn't empty, we continue taking items.
                    Item* itemChest = dynamic_cast<Item*>(chest->getContains().front());
                    if (itemChest != nullptr) {
                        std::cout << "  ->  " << itemChest->getName() << " : " << itemChest->getDescription() << "   " << itemChest->getAmount() << " uds. " << std::endl;
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


/*
    @brief Method to select an item from the inventory.
    @param command Vector that contains the command entered by the player.
*/
void Player::selectItem(const std::vector<std::string>& command) {
    if (command.size() > 1) {
        for (const auto& it : getContains()) {
            Item* item = dynamic_cast<Item*>(it);

            if (item != nullptr) {
                if (item->getName() == Utils::getFullNameItem(command, command.size() - 1)) {
                    selectedItem = item;
                    std::cout << "You have selected: " << item->getName() << std::endl;
                    break;
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
void Player::useItemHealer() { 
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
            passTurnEnemy();

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
            passTurnEnemy();

        } else if (selectedItem->getItemType() == ItemType::KIT) {

            if (getHealth() == MAX_HEALTH) {
                std::cout << "You can't take the Kit." << std::endl;
            } else {
                setHealth(MAX_HEALTH);
                decreaseAmountItem();
                std::cout << "Healing with a Kit...." << std::endl;
            }
            passTurnEnemy();

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
            passTurnEnemy();
        }
    } else {
        std::cout << "You don't have items selected to use." << std::endl;
    }
}


/*
    @brief Method to reduce the amount of an item, if the amount reaches 0, we delete the item.
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
    if (selectedItem != nullptr) {
        for (const auto& it : getLocation()->getContains()) {
            Exit* exit = dynamic_cast<Exit*>(it); //Pointer to the exit.

            if (exit != nullptr) {
                if (exit->getDirectionType() == command[1]) {
                    if (exit->getBlocked()) {
                        exit->openExit(selectedItem);
                    }
                    break;
                }
            }
        }
    }
    else {
        std::cout << "You need to have the correct object selected to open the door." << std::endl;
    }
}


/*
    @brief Method to close a open exit.
    @param command Vector that contains the command entered by the player.
*/
void Player::closeExit(const std::vector<std::string>& command) {
    if (selectedItem != nullptr) {
        for (const auto& it : getLocation()->getContains()) {
            Exit* exit = dynamic_cast<Exit*>(it);

            if (exit != nullptr) {
                if (exit->getDirectionType() == command[1]) {
                    if (!exit->getBlocked()) {
                        exit->closeExit(selectedItem);
                    }
                    break;
                }
            }
        }
    }
    else {
        std::cout << "You need to have the correct object selected to open the door." << std::endl;
    }
}


/*
    @brief Method to move the player around the map.
    @param command Vector that contains the command entered by the player.
*/
void Player::movePlayer(const std::vector<std::string>& command) {
    if (command.size() == 2) {
        for (const auto& it : getLocation()->getContains()) {
            Exit* exit = dynamic_cast<Exit*>(it); 

            if(exit != nullptr){
                if (exit->getDirectionType() == command[1]) {
                    if (exit->getBlocked()) {
                        std::cout << "The exit is blocked. You need " << exit->getKey()->getName() << " to open." << std::endl;
                    } else {
                        std::cout << "You've moved to the room " << exit->getDestination()->getName() << std::endl;
                        getLocation()->removeEntity(this);
                        exit->getDestination()->addContains(this);
                        setLocation(exit->getDestination());
                        selectedNPC = nullptr;
                        findEnemie();
                    }
                    break;
                }
            }
        }
    }
}


/*
    @brief Method to take automatically gold or ammunition from the floor of the room.
*/
void Player::autoTake() {
    std::list<Item*> addItemsInventory;
    
    for (const auto& it : getLocation()->getContains()) {
        Item* item = dynamic_cast<Item*>(it);

        if (item != nullptr) {
            if (item->getItemType() == ItemType::GOLD) {
                addItemsInventory.push_back(item);
            } else if (item->getItemType() == ItemType::AMMUNITION) {
                addItemsInventory.push_back(item);
            }
        }
    }

    for (const auto& it : addItemsInventory) {
        if (it->getItemType() == ItemType::GOLD) {
            if (getGold() < MAX_GOLD) {
                int newGold = getGold() + it->getAmount();

                if (newGold > MAX_GOLD) {
                    int difGold = newGold - MAX_GOLD;

                    std::cout << std::endl << " + " << MAX_GOLD - getGold() << " gold." << std::endl;
                    setGold(MAX_GOLD);
                    it->setAmount(difGold);
                } else {
                    std::cout << std::endl << " + " << it->getAmount() << " gold." << std::endl;
                    setGold(newGold);
                    getLocation()->removeEntity(it);
                    getWorld()->removeEntity(it);
                }
            }
        } else if (it->getItemType() == ItemType::AMMUNITION) {
            if (numAmmo < MAX_AMMUNATION) {
                int newAmmo = numAmmo + it->getAmount();

                if (newAmmo > MAX_AMMUNATION) {
                    int difAmmo = newAmmo - MAX_AMMUNATION;

                    std::cout << std::endl << " + " << MAX_AMMUNATION - numAmmo << " ammo." << std::endl;
                    setAmmo(MAX_AMMUNATION);
                    it->setAmount(difAmmo);
                } else {
                    std::cout << std::endl << " + " << it->getAmount() << " ammo." << std::endl;
                    setAmmo(newAmmo);
                    getLocation()->removeEntity(it);
                    getWorld()->removeEntity(it);
                }
            }
        }
    }
}


/*
    @brief Method to talk with the NPC in the room
*/
void Player::talkNPC() {
    if (selectedNPC != nullptr && selectedNPC->getType() == NPCType::ENEMIES) {
        std::cout << "First you must to kill the enemies..." << std::endl;
    } else {
        for (const auto& it : getLocation()->getContains()) {
            NPC* npc = dynamic_cast<NPC*>(it);

            if (npc != nullptr) {
                if (npc->getType() == NPCType::SELLER) {
                    std::cout << "Welcome to my shop, I'm " << npc->getName() << ". How can I help you?" << std::endl;
                    selectedNPC = npc;
                }
            }
        }
    }
    
}


/*
    @brief Method to view the items of the vendor NPC.
*/
void Player::viewShop() {
    if (selectedNPC != nullptr) {
        if (selectedNPC->getType() == NPCType::SELLER) {
            selectedNPC->showShop();
        }
    }
}


/*
    @brief Method to view all NPCs in the room.
*/
void Player::viewRadar() {
    std::cout << "==================================================" << std::endl;
    std::cout << "                       RADAR                      " << std::endl;
    std::cout << "==================================================" << std::endl;

    std::list<NPC*> npcRoom;
    for (const auto& it : getLocation()->getContains()) {
        NPC* npc = dynamic_cast<NPC*>(it);

        if (npc != nullptr) {
            npcRoom.push_back(npc);
        }
    }

    if (npcRoom.empty()) {
        std::cout << "             The room is empty of NPCs.          " << std::endl << std::endl;
    } else {
        for (const auto& it : npcRoom) {
            std::cout << "  ->  " << it->getName() << " : " << it->getDescription() << std::endl;
        }
    }
    std::cout << "==================================================" << std::endl;
}


/*
    @brief Method to buy an item from the NPC seller.
    @param command Vector that contains the command entered by the player.
*/
void Player::buyItemShop(const std::vector<std::string>& command) {
    if (selectedNPC != nullptr) {
        if (selectedNPC->getType() == NPCType::SELLER) {
            if (getContains().size() < MAX_ITEM_INVENTORY) {
                Item* itemBuy = selectedNPC->buyItem(Utils::getFullNameItem(command, command.size() - 1), getGold());

                if (itemBuy != nullptr) {
                    addContains(itemBuy);
                    setGold(getGold() - itemBuy->getPrice());
                    std::cout << itemBuy->getName() << " purchased successfully. Thank you." << std::endl;
                }
            } else {
                std::cout << "You can't buy the " << Utils::getFullNameItem(command, command.size() - 1) << " because your inventory is full." << std::endl;
            }
        }
    }
}


/*
    @brief Method to sell an item to an NPC seller.
    @param command Vector that contains the command entered by the player.
*/
void Player::sellItemShop(const std::vector<std::string>& command) {
    if (selectedNPC != nullptr) {
        if (selectedNPC->getType() == NPCType::SELLER) {
            for (const auto& it : getContains()) {
                Item* item = dynamic_cast<Item*>(it);

                if (item != nullptr) {
                    if (item->getName() == Utils::getFullNameItem(command, command.size() - 1)) {
                        if (selectedNPC->sellItem(item)) {
                            int newGold = getGold() + item->getPrice();

                            if (newGold > MAX_GOLD) {
                                int difGold = newGold - MAX_GOLD;
                                setGold(MAX_GOLD);
                                Item* gold = new Item("Gold", "Gold to buy items in the shop", EntityType::ITEM, ItemType::GOLD, difGold, 1, 0);
                                getLocation()->addContains(gold);
                                getWorld()->addEntity(gold);
                            } else {
                                setGold(newGold);
                            }
                            std::cout << item->getName() << " sold successfully. Thank you." << std::endl;
                            removeContains(item);
                        }
                    }
                }
            }
        }
    }
}


/*
    @brief Method to make damage to NPC enemies.
*/
void Player::shootEnemies() {
    if (selectedNPC != nullptr) {
        if (selectedNPC->getType() == NPCType::ENEMIES) {
            if (selectedItem != nullptr) {
                if (selectedItem->getItemType() == ItemType::RIFLE || selectedItem->getItemType() == ItemType::SHOTGUN) {
                    if (numAmmo > 0) {
                        --numAmmo;
                        selectedNPC->receiveDamage(selectedItem->getValue());
                        passTurnEnemy();

                        if (selectedNPC->getHealth() == 0) {
                            ++numKills;
                            std::cout << "Congratulations, you have defeated the enemy " << selectedNPC->getName() << std::endl;
                            std::cout << "==================================================" << std::endl;
                            std::cout << " Items Enemy                                      " << std::endl;
                            std::cout << "--------------------------------------------------" << std::endl;

                            for (const auto& it : selectedNPC->getContains()) {
                                Item* item = dynamic_cast<Item*>(it);

                                if (item != nullptr) {
                                    getLocation()->addContains(item);
                                    std::cout << "  ->  " << item->getName() << " : " << item->getDescription() << "   " << item->getAmount() << " uds. " << std::endl;
                                }
                            }
                            std::cout << "==================================================" << std::endl;

                            getLocation()->removeEntity(selectedNPC);
                            getWorld()->removeEntity(selectedNPC);
                            selectedNPC = nullptr;
                        } else {
                            std::cout << " ->" << selectedNPC->getName() << "   Health: " << selectedNPC->getHealth() << "  Shield: " << selectedNPC->getShield() << "  Ammo:" << numAmmo << std::endl;
                        }
                    } else {
                        std::cout << "You don't have more bullets. RUNN!!!" << std::endl;
                    }
                } else {
                    std::cout << "You can't shoot the enemies you need a Rifle or a Shotgun to do that." << std::endl;
                }
            }
        }
    }
}


/*
    @brief Method to see if there is an enemy in the room.
*/
void Player::findEnemie() {
    for (const auto& it : getLocation()->getContains()) {
        NPC* enemy = dynamic_cast<NPC*>(it);

        if (enemy != nullptr) {
            if (enemy->getType() == NPCType::ENEMIES) {
                std::cout << "!!!!! A wild " << enemy->getName() << " appears in the room!!!!!" << std::endl;
                std::cout << " ->" << enemy->getName() << "   Health: " << enemy->getHealth() << "  Shield: " << enemy->getShield() << std::endl;
                selectedNPC = enemy;
                break;
            }
        }
    }
}


/*
    @brief Method to pass the main player's turn to the NPC.
*/
void Player::passTurnEnemy() {
    if (selectedNPC != nullptr) {
        if (selectedNPC->getType() == NPCType::ENEMIES) {
            getWorld()->setPlayerTurn(false);
        }
    }
}


/*
    @brief Method to update the Main Player.
*/
void Player::Update() {
    autoTake();
}