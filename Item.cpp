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
Item::Item(const std::string& name, const std::string& description, EntityType type, ItemType iType, const int& amount, const int& value) : Entity(name, description, type), type(iType), amount(amount), value(value) {

}


/*
	@brief Destructor of the Item class.
*/
Item::~Item() {

}