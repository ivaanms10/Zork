#ifndef CREATURE_H
#define CREATURE_H

#include "Room.h"

static const int MAX_HEALTH = 100;
static const int MAX_BANDAGES_HEALTH = 75;
static const int MAX_SMALL_SHIELD = 50;
static const int MAX_SHIELD = 100;

class Creature : public Entity{
	private:
		Room* location;
		int health;
		int shield;

	public:
		Creature();
		Creature(const std::string& name, const std::string& description, EntityType type, Room* location, const int& health, const int& shield);
		~Creature();

		std::string getName() const { return Entity::getName(); } //Method to get the creature name.
		int getHealth() const { return health; } //Method to get the creature health.
		int getShield() const { return shield; } //Method to get the creature shield.
		Room* getLocation() const { return location; } //Method to get the creature room.

		void setLocation(Room* newLocation) { this->location = newLocation; } //Method to set a new creature room.
		void setShield(const int& shield) { this->shield = shield; } //Method to set a new value of shield.
		void setHealth(const int& health) { this->health = health; } //Method to set a new value of health.

};

#endif // !CREATURE_H