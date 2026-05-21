#include "Item.h"

/*
	@brief Default constructor of the Item class.
*/
Item::Item() : Entity("", "", EntityType::ITEM) {

}


/*
	@brief Parameterized constructor of the Item class.
	@param name Name of the item.
	@param description Description of the item.
	@param type Type of entity.
*/
Item::Item(const std::string& name, const std::string& description, EntityType type) : Entity(name, description, type) {

}


/*
	@brief Destructor of the Item class.
*/
Item::~Item() {

}