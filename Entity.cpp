#include "Entity.h"

/*
	@brief Default constructor of the Entity class.
*/
Entity::Entity() : type(EntityType::ENTITY), name(""), description("") {
	
}


/*
	@brief Parameterized constructor of the Entity class.
	@param name Name of the entity.
	@param description Description of the entity.
	@param type Type of entity.
*/
Entity::Entity(const std::string& name, const std::string& description, EntityType type) : type(type), name(name), description(description) {

}


/*
	@brief Destructor of the Entity class.
*/
Entity::~Entity() {

}


/*
	@brief Method to update the entity states during the game.
*/
void Entity::Update() {

}