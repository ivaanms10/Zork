#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

//Enum with the types of entities.
enum class ItemType {
	ITEM,
	CHEST,  
	BIG_SHIELD, //50 Shield
	SMALL_SHIELD, //25 Shield
	KIT, //100 Health
	BANDAGES, //15 Health
	RIFLE, //25 Damage
	SHOTGUN, //90 Damage
	UTILITY, //Keys to open chest and doors.
	AMMUNITION, //Ammo for the weapon.
	GOLD //Gold to buy new item in the shop.
};


class Item : public Entity{
	private:
		ItemType type;
		int amount;
		int value; 

	public:
		Item();
		Item(const std::string& name, const std::string& description, EntityType type, ItemType iType, const int& amount, const int& value);
		~Item();
};

#endif // !ITEM_H