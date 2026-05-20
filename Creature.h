#ifndef CREATURE_H
#define CREATURE_H

#include "Room.h"

class Creature : public Entity{
	private:
		std::string name;
		Room* location;
		int health;

	public:
		Creature();
		Creature(const std::string& name, Room* location, const int& health);
		~Creature();
};

#endif // !CREATURE_H