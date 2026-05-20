#ifndef EXIT_H
#define EXIT_H

#include "Room.h"

//Enum with the 4 possible directions.
enum class DirectionType {
	NORTH,
	SOUTH, 
	EAST,
	WEST
};


class Exit : public Entity{
	private:
		DirectionType direction;
		Room* source; 
		Room* destination;

	public:
		Exit();
		Exit(DirectionType direction, Room* source, Room* destination);
		~Exit();

};

#endif // !EXIT_H