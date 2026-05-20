#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

static const int MAX_HEALTH = 100;

class Player : public Creature{
	private:
		int shield;

	public:
		Player();
		Player(const std::string& name, Room* location);
		~Player();

};

#endif // !PLAYER_H