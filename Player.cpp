#include "Player.h"

/*
	@brief Default constructor of the Player class.
*/
Player::Player() : Creature("", "", EntityType::PLAYER, nullptr, MAX_HEALTH, 0), numKills(0), numDeath(0), numGold(0) {

}


/*
	@brief Parameterized constructor of the Player class.
	@param name Player name.
	@param location Room where the player is located.
*/
Player::Player(const std::string& name, const std::string& description, Room* location) : Creature(name, description, EntityType::PLAYER, location, MAX_HEALTH, 0), numKills(0), numDeath(0), numGold(0){

}


/*
	@brief Destructor of the Player class.
*/
Player::~Player(){
    
}

/*
    @brief Method to show in the screen the player stats.
*/
void Player::stats() const{
    std::cout << "==================================================" << std::endl;
    std::cout << "                 PERFIL DE JUGADOR                " << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << " Nick: " << Creature::getName() << "              " << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    std::cout << " HEALTH:  " << Creature::getHealth() << " / 100"    << std::endl;
    std::cout << " SHIELD: " << Creature::getShield() << " / 100"     << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " MARCADOR:\n";
    std::cout << " Kills:   " << numKills << "                 Muertes: " << numDeath << std::endl;
    std::cout << " Gold:  " << numGold << std::endl;
    std::cout << "==================================================" << std::endl;
}