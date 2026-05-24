#ifndef NPC_H
#define NPC_H

#include "Creature.h"
#include <string>

class Room;
class World;

//Enum with the 4 possible directions.
enum class NPCType {
	ENEMIES,
	FRIENDLY,
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
		
		NPCType getType() const { return type; } //Method to get the type of NPC.
};

#endif // !NPC_H