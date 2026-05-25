#ifndef NPC_H
#define NPC_H

#include "Creature.h"
#include <string>

static const int MAX_DAMAGE_ENEMIE = 50;
static const int MIN_DAMAGE_ENEMIE = 50;


class Room;
class World;
class Item;

//Enum with the 4 possible directions.
enum class NPCType {
	ENEMIES,
	SELLER
};


class NPC : public Creature{
	private:
		NPCType type; 

	public:
		NPC();
		NPC(const std::string& name, const std::string& description, NPCType type, Room* location, World* world);
		~NPC();

		void showShop() const;
		Item* buyItem(const std::string& itemName, int goldPlayer);
		bool sellItem(Item* item);
		void attackPlayer();
		void Update();
		
		NPCType getType() const { return type; } //Method to get the type of NPC.
};

#endif // !NPC_H