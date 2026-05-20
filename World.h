#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include <vector>
#include <string>

class World{
	private:
		std::vector<Entity*> entities;
	public:
		World();
		World(std::vector<Entity*> entities);
		~World();

		void createWorld();
		void processCommand(const std::vector<std::string> &command);
};

#endif // !WORLD_H