#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>

class Player;
class Entity;

class World{
	private:
		Player* player;
		std::vector<Entity*> entities;

	public:
		World();
		~World();

		void createWorld();
		void processCommand(const std::vector<std::string> &command);
		void addEntity(Entity* entity) { entities.push_back(entity); } //Method to add a new entity.
		void removeEntity(Entity* entity);
		
		void movePlayer(const std::vector<std::string>& command);

};

#endif // !WORLD_H