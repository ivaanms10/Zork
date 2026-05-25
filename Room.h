#ifndef ROOM_H
#define ROOM_H

#include "Entity.h"
#include <string>


class Room : public Entity{
	public:
		Room();
		Room(const std::string& name, const std::string& description);
		~Room();

		void Update();
		void showRoom() const;
		void showExits() const;

		void addEntity(Entity* entity) { Entity::addContains(entity); } //Method to add a new entity to the room.
		void removeEntity(Entity* entity) { Entity::removeContains(entity); } //Method to remove an entity from the room.
};

#endif // !ROOM_H