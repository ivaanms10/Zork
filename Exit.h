#ifndef EXIT_H
#define EXIT_H

#include "Entity.h"
#include <string>

class Room;
class Item;

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
		bool isBlocked;
		Item* key;

	public:
		Exit();
		Exit(DirectionType direction, Room* source, Room* destination, const std::string& name, const std::string& description, bool isBlocked, Item* key);
		~Exit();

		std::string getDirectionType() const;
		Room* getSource() const { return source; } //Method to get the source room.
		Room* getDestination() const { return destination; } //Method to get the destination room.
		bool getBlocked() const { return isBlocked; } //Method to know if the exit is open or not. 
		Item* getKey() const { return key; } //Method to get the key.

		bool openExit(Item* key);
		bool closeExit(Item* key);
};

#endif // !EXIT_H