#pragma once
#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "item.hpp"
#include "weapon.hpp"
#include "armour.hpp"

#include <list>
#include <utility>
#include <iostream>

class Inventory
{
public:
	//Whilst weapons and armour are items, they have their own 
	//specific properties and can't be stored in the same list.
	//The first element of the pair stores a pointer to the item
	//in the item/weapon/armour atlas, defined in main(), the second
	//if the quantity of the item

	std::list<std::pair<Item*, int>> items;
	std::list<std::pair<Weapon*, int>> weapons;
	std::list<std::pair<Armour*, int>> armour;

	Inventory(){};
	Inventory(std::list<std::pair<Item*, int>> items,
		std::list<std::pair<Weapon*, int>> weapons,
		std::list<std::pair<Armour*, int>> armour);
	
	void add_item(Item* item, int count);
	void add_weapon(Weapon* weapon, int count);
	void add_armour(Armour* armour, int count);
};

Inventory::Inventory(std::list<std::pair<Item*, int>> items,
		std::list<std::pair<Weapon*, int>> weapons,
		std::list<std::pair<Armour*, int>> armour)
{
	this->items = items;
	this->weapons = weapons;
	this->armour = armour;
}

//add an item to the inventory
void Inventory::add_item(Item* item, int count)
{
	//increase quantity if the item already exists
	for(std::list<std::pair<Item*, int> >::iterator it =
		this->items.begin(); it < this->items.end(); ++it)
	{
		if(it.first == item)
		{
			it.second += count;
			return;
		}
		//if the item doesn't already exist, then a pair must be created
		this->items.push_back(std::make_pair(item, count));
	}
}
void Inventory::add_weapon(Weapon* weapon, int count)
{
	//increase quantity if the item already exists
	for(std::list<std::pair<Weapon*, int> >::iterator it =
		this->weapons.begin(); it < this->weapons.end(); ++it)
	{
		if(it.first == weapon)
		{
			it.second += count;
			return;
		}
		//if the item doesn't already exist, then a pair must be created
		this->weapons.push_back(std::make_pair(weapon, count));
	}
}

void Inventory::add_armour(Armour* armour, int count)
{
	//increase quantity if the item already exists
	for(std::list<std::pair<Armour*, int> >::iterator it =
		this->armour.begin(); it < this->armour.end(); ++it)
	{
		if(it.first == armour)
		{
			it.second += count;
			return;
		}
		//if the item doesn't already exist, then a pair must be created
		this->armour.push_back(std::make_pair(armour, count));
	}
}

#endif //INVENTORY_HPP