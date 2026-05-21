#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item : public Entity{
	private:
		

	public:
		Item();
		Item(const std::string& name, const std::string& description, EntityType type);
		~Item();
};

#endif // !ITEM_H