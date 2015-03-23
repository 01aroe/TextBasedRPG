#pragma once
#ifndef AREA_HPP
#define AREA_HPP

#include "inventory.hpp"
#include "creature.hpp"
#include "dialogue.hpp"

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

	//creatures contained within the area. Currently only one
	//due to battle class mechanics.
	std::vector<Creature*> creatures;

	Area(Dialogue dialogue, Inventory inventory, 
		std::vector<Creature*> creatures);

	void search(Creature& player);
};

Area::Area(Dialogue dialogue, Inventory inventory, 
	std::vector<Creature*> creatures)
{
	this->dialogue = dialogue;
	this->items = items;
	this->creatures = creatures;
}

void Area::search(Creature& player)
{
	std::cout << "You find: " << std::endl;

	this->items.print();
	player.inventory.merge(&(this->items));
	this->items.clear();

	return;

}
#endif //AREA_HPP