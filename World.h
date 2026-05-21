#ifndef WORLD_H
#define WORLD_H

#include "Exit.h"
#include "Player.h"
#include <vector>


class World{
	private:
		Player* player;
		std::vector<Entity*> entities;
	public:
		World();
		World(Player* player, std::vector<Entity*> entities);
		~World();

		void createWorld();
		void processCommand(const std::vector<std::string> &command);
};

#endif // !WORLD_H