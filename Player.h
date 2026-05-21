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
		Player(const std::string& name, Room* location);
		~Player();

		void stats() const;

};

#endif // !PLAYER_H