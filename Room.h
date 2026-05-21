#ifndef ROOM_H
#define ROOM_H

#include "Entity.h"


class Room : public Entity{
	private:

	public:
		Room();
		Room(const std::string& name, const std::string& description);
		~Room();

		void Update();
		
		void showRoom() const;

		void addEntity(Entity* entity) { Entity::addContains(entity); } //Method to add a new entity to the room.

};

#endif // !ROOM_H