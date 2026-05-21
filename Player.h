#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

class Player : public Creature{
	private:
		int numKills = 0;
		int  numDeath = 0;
		int numGold = 0; //Gold to buy new Items.

	public:
		Player();
		Player(const std::string& name, const std::string& description, Room* location);
		~Player();

		void stats() const;
		void look() { std::cout << "You are in the room: " << Creature::getLocation()->getName() << std::endl; }
};

#endif // !PLAYER_H