#include "Player.h"

/*
	@brief Default constructor of the Player class.
*/
Player::Player() : Creature("", nullptr, MAX_HEALTH, 0), numKills(0), numDeath(0) {

}


/*
	@brief Parameterized constructor of the Player class.
	@param name Player name.
	@param location Room where the player is located.
*/
Player::Player(const std::string& name, Room* location) : Creature(name, location, MAX_HEALTH, 0), numKills(0), numDeath(0){

}


/*
	@brief Destructor of the Player class.
*/
Player::~Player(){

}


void Player::stats() const{
    std::cout << "==================================================\n";
    std::cout << "                 PERFIL DE JUGADOR                \n";
    std::cout << "==================================================\n";
    std::cout << " Nick: " << Creature::getName() << "                             \n";
    std::cout << "--------------------------------------------------\n";

    std::cout << " HEALTH:  " << Creature::getHealth() << " / 100\n";
    std::cout << " SHIELD: " << Creature::getShield() << " / 100\n";

    std::cout << "--------------------------------------------------\n";
    std::cout << " MARCADOR:\n";
    std::cout << " Kills:   " << numKills << "          Muertes: " << numDeath << "\n";
    std::cout << " Gold:  " << numGold << "\n";
    std::cout << "==================================================\n";
}