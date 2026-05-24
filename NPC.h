#ifndef NPC_H
#define NPC_H

#include "Creature.h"

class Room;
class World;

class NPC : public Creature{
	private:

	public:
		NPC();
		NPC(const std::string& name, const std::string& description, Room* location, World* world);
		~NPC();

};

#endif // !NPC_H