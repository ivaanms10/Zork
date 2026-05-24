#include "Item.h"

/*
	@brief Default constructor of the Item class.
*/
Item::Item() : Entity("", "", EntityType::ITEM), type(ItemType::ITEM), amount(1), value(1) {

}


/*
	@brief Parameterized constructor of the Item class.
	@param name Name of the item.
	@param description Description of the item.
	@param type Type of entity.
	@param iType Type of item.
	@param amount Number of items.
	@param value Value of the item.
*/
Item::Item(const std::string& name, const std::string& description, EntityType type, ItemType iType, int amount, int value) : Entity(name, description, type), type(iType), amount(amount), value(value) {

}


/*
	@brief Destructor of the Item class.
*/
Item::~Item() {

}


/*
    @brief Method to get the max amount of an item.
    @return The max amount of the item.
*/
int Item::getMaxAmount() const {
    switch (this->type) {
        case ItemType::CHEST:
            return MAX_CHEST;
        case ItemType::BIG_SHIELD:
            return MAX_BIG;
        case ItemType::SMALL_SHIELD:
            return MAX_SMALL; 
        case ItemType::KIT:
            return MAX_KIT;
        case ItemType::BANDAGES:
            return MAX_BANDAGES;
        case ItemType::RIFLE:
            return MAX_RIFLE;
        case ItemType::SHOTGUN:
            return MAX_SHOTGUN;
        case ItemType::KEY:
            return MAX_KEY;
        case ItemType::AMMUNITION:
            return MAX_AMMUNATION;
        case ItemType::GOLD:
            return MAX_GOLD;
    }
    return 1;
}