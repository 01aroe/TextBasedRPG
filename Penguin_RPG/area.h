#ifndef AREA_H
#define AREA_H

#include "inventory.h"
#include "creature.h"
#include "dialogue.h"

#include <vector>

//Movement is achieved through areas, which are contained
//units of space consisting of an inventory, a list of creatures
//and dialogues.
class Area
{
public:
	Area(){};

	//dialogue is run whenever the area is entered
	Dialogue dialogue;

	//items contained within the area
	Inventory items;
	//Inventory weapons;

	//creatures contained within the area. Currently only one
	//due to battle class mechanics.
	std::vector<Creature*> creatures;

	Area(Dialogue dialogue, Inventory items,
		std::vector<Creature*> creatures) :
		dialogue(dialogue), items(items), creatures(creatures){};

	void search(Creature& player)
	{
		std::cout << "You stumble upon: " << std::endl;
		this->items.print();
		player.inventory.merge(&(this->items));
		this->items.clear();
		return;
	}
};
#endif //AREA_H