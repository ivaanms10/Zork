#include "Player.h"

/*
	@brief Default constructor of the Player class.
*/
Player::Player() : Creature(nullptr,"") {

}


/*
	@brief Parameterized constructor of the Player class.
	@param location Room where the player is located.
	@param name Player name.
*/
Player::Player(Room* location, const std::string& name) : Creature(location, name) {

}


/*
	@brief Destructor of the Player class.
*/
Player::~Player(){

}