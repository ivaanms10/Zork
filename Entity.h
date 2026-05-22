#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "Utils.h"

//Enum with the types of entities.
enum class EntityType{
	ENTITY,
	CREATURE,
	NPC,
	PLAYER,
	EXIT,
	ROOM,
	ITEM
};


class Entity {
	private:
		EntityType type;
		std::string name;
		std::string description;
		std::list<Entity*> contains;

	public:
		Entity();
		Entity(const std::string& name, const std::string& description, EntityType type);
		virtual ~Entity();

		virtual void Update();

		EntityType getType() const { return type; } //Method to get the type of entity.
		std::string getName() const { return name; } //Method to get the name entity.
		std::string getDescription() const { return description; } //Method to get the description entity.
		std::list<Entity*> getContains() const { return contains; } //Method to get the contains.

		void addContains(Entity* entity) { this->contains.push_back(entity); } //Method to add a new entity to the contains list.
		void removeContains(Entity* entity) { this->contains.remove(entity); } //Method to remove an entity from the contains list.
};

#endif // !ENTITY_H