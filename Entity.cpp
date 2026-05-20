#include "Entity.h"

/*
	@brief Default constructor of the Entity class.
*/
Entity::Entity() : name(""), description(""), type(ENTITY){
	
}


/*
	@brief Parameterized constructor of the Entity class.
	@param name Name of the entity.
	@param description Description of the entity.

*/
Entity::Entity(const std::string& name, const std::string& description) : name(name), description(description), type(ENTITY){

}


/*
	@brief Destroyer of the Entity class.
*/
Entity::~Entity() {

}