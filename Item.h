#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include <string>

static const int MAX_CHEST = 1;
static const int MAX_BIG = 3;
static const int MAX_SMALL = 6;
static const int MAX_KIT = 3;
static const int MAX_BANDAGES = 15;
static const int MAX_RIFLE = 1;
static const int MAX_SHOTGUN = 1;
static const int MAX_UTILITY = 1;
static const int MAX_AMMUNATION = 100;
static const int MAX_GOLD = 500;

//Enum with the types of entities.
enum class ItemType {
	ITEM,
	CHEST,  
	BIG_SHIELD, 
	SMALL_SHIELD, 
	KIT, 
	BANDAGES, 
	RIFLE, 
	SHOTGUN, 
	UTILITY, 
	AMMUNITION, 
	GOLD 
};


class Item : public Entity{
	private:
		ItemType type;
		int amount;
		int value; 

	public:
		Item();
		Item(const std::string& name, const std::string& description, EntityType type, ItemType iType, int amount, int value);
		~Item();

		ItemType getItemType() const { return type; } //Method to get the type of item.
		int getAmount() const { return amount; } //Method to get the amount of the item.
		int getValue() const { return value; } //Method to get the value of the item.
		int getMaxAmount() const;
		
		void setAmount(int amount) { this->amount = amount; } //Method to set a new amount.
		void decreaseAmount() { this->amount -= 1; } //Method to decrease the amount.
};

#endif // !ITEM_H