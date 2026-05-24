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
		int numAmmo = 0;

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
		void deselectItem();
		void useItemHealer();
		void openExit(const std::vector<std::string>& command);
		void closeExit(const std::vector<std::string>& command);
		void movePlayer(const std::vector<std::string>& command);
		void autoTake();

		void decreaseAmountItem();
		Item* existItemInventory(Item* item);
		
		void setGold(int numGold) { this->numGold = numGold; } //Method to set a new amount of gold.
		void setAmmo(int numAmmo) { this->numAmmo = numAmmo; } //Method to set a new amount of gold.
};

#endif // !PLAYER_H