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
};

#endif // !ROOM_H