#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"


class Player : public Creature{
	private:

	public:
		Player();
		Player(Room* location, const std::string& name);
		~Player();

};

#endif // !PLAYER_H