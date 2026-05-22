#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Item.h"

static const int MAX_ITEM_INVENTORY = 5;

class Player : public Creature{
	private:
		Item* selectedItem = nullptr;
		int numKills = 0;
		int numDeath = 0;
		int numGold = 0; //Gold to buy new Items.

	public:
		Player();
		Player(const std::string& name, const std::string& description, Room* location);
		~Player();

		void statsPlayer() const;
		void takeItem(const std::vector<std::string>& command);
		void dropItem(const std::vector<std::string>& command);
		void showInventory() const;
		void openChest(const std::vector<std::string>& command);
		void selectItem(const std::vector<std::string>& command);
		void useItem(const std::vector<std::string>& command);
		void decreaseAmountItem();

};

#endif // !PLAYER_H