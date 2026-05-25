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
		bool playerTurn;

	public:
		World();
		~World();

		void createWorld();
		void processCommand(const std::vector<std::string> &command);
		void removeEntity(Entity* entity);
		void respawnEnemies();
		void Update();

		void addEntity(Entity* entity) { entities.push_back(entity); } //Method to add a new entity.
		Player* getPlayer() const { return player; } //Method to get the pointer to the Main Player.
		void setPlayerTurn(bool playerTurn) { this->playerTurn = playerTurn; } //Method to set a new value to the Player Turn.
};

#endif // !WORLD_H