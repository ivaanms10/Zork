#ifndef CREATURE_H
#define CREATURE_H

#include "Room.h"

class Creature{
	private:
		Room* location;
		std::string name;

	public:
		Creature();
		Creature(Room* location, const std::string& name);
		~Creature();
};

#endif // !CREATURE_H