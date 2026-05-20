#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <string>

//Enum with the types of entities.
enum EntityType {
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
		Entity(const std::string& name, const std::string& description);
		virtual ~Entity();
};

#endif // !ENTITY_H