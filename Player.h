#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Item.h"

static const int MAX_ITEM_INVENTORY = 5;

class Player : public Creature{
	private:
		int numKills = 0;
		int numDeath = 0;
		int numGold = 0; //Gold to buy new Items.

	public:
		Player();
		Player(const std::string& name, const std::string& description, Room* location);
		~Player();

		void statsPlayer() const;
		void takeItem(Item* item);
		void showInventory() const;
};

#endif // !PLAYER_H