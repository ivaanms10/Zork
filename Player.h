#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include <string>
#include <vector>

class Item;
class Room;
class World;

static const int MAX_ITEM_INVENTORY = 5;

class Player : public Creature{
	private:
		Item* selectedItem = nullptr;
		int numKills = 0;
		int numDeath = 0;
		int numGold = 0; //Gold to buy new Items.

	public:
		Player();
		Player(const std::string& name, const std::string& description, Room* location, World* world);
		~Player();

		void statsPlayer() const;
		void showInventory() const;
		void takeItem(const std::vector<std::string>& command);
		void dropItem(const std::vector<std::string>& command);
		void dropItemSelected(const std::vector<std::string>& command);
		void dropItemAmount(int amount, Item* item);
		void openChest(const std::vector<std::string>& command);
		void selectItem(const std::vector<std::string>& command);
		void useItemSelected();
		void openExit(const std::vector<std::string>& command);
		void closeExit(const std::vector<std::string>& command);
		void movePlayer(const std::vector<std::string>& command);

		void decreaseAmountItem();
		Item* existItemInventory(Item* item);
};

#endif // !PLAYER_H