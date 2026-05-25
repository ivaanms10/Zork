#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"
#include <string>

class Room;
class World;

static const int MAX_HEALTH = 100;
static const int MAX_BANDAGES_HEALTH = 75;
static const int MAX_SMALL_SHIELD = 50;
static const int MAX_SHIELD = 100;
static const int MAX_GOLD_CREATURE = 2000;


class Creature : public Entity{
	private:
		World* world;
		Room* location;
		int health;
		int shield;
		int numGold;

	public:
		Creature();
		Creature(World* world, const std::string& name, const std::string& description, EntityType type, Room* location, int health, int shield, int gold);
		~Creature();

		void receiveDamage(int damage);

		int getHealth() const { return health; } //Method to get the creature health.
		int getShield() const { return shield; } //Method to get the creature shield.
		Room* getLocation() const { return location; } //Method to get the creature room.
		World* getWorld() const { return world; } //Method to get the world.
		int  getGold() const { return numGold; } //Method to get the amount of gold.

		void setLocation(Room* newLocation) { this->location = newLocation; } //Method to set a new creature room.
		void setShield(int shield) { this->shield = shield; } //Method to set a new value of shield.
		void setHealth(int health) { this->health = health; } //Method to set a new value of health.
		void setGold(int gold) { this->numGold = gold; } //Method to set a new amount of gold.
};

#endif // !CREATURE_H