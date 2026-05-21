#ifndef CREATURE_H
#define CREATURE_H

#include "Room.h"

static const int MAX_HEALTH = 100;
static const int MAX_SHIELD = 100;

class Creature : public Entity{
	private:
		std::string name;
		Room* location;
		int health;
		int shield;

	public:
		Creature();
		Creature(const std::string& name, Room* location, const int& health, const int& shield);
		~Creature();

		std::string getName() const { return name; }
		int getHealth() const { return health; }
		int getShield() const { return shield; }

};

#endif // !CREATURE_H