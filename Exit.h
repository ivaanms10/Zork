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
		Exit(DirectionType direction, Room* source, Room* destination, const std::string& name, const std::string& description);
		~Exit();

		std::string getDirectionType() const;
		Room* getSource() const { return source; } //Method to get the source room.
		Room* getDestination() const { return destination; } //Method to get the destination room.

};

#endif // !EXIT_H