#include "Player.h"

/*
	@brief Default constructor of the Player class.
*/
Player::Player() : Creature("", nullptr, MAX_HEALTH), shield(0) {

}


/*
	@brief Parameterized constructor of the Player class.
	@param name Player name.
	@param location Room where the player is located.
	@param health Number of lives the player has.
*/
Player::Player(const std::string& name, Room* location) : Creature(name, location, MAX_HEALTH), shield(0) {

}


/*
	@brief Destructor of the Player class.
*/
Player::~Player(){

}