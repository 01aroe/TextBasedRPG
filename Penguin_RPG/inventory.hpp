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

	void remove_item(Item*, int count);
	void remove_weapon(Weapon*, int count);
	void remove_armour(Armour*, int count);

	void merge(Inventory* inventory);
	void clear();

	int print_items(bool label);
	int print_weapons(bool label);
	int print_armour(bool label);
	void print(bool label);
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
	for(auto& it : this->items)
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
	for(auto& it : this->weapons)
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
	for(auto& it : this->armour)
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

void Inventory::remove_item(Item*, int count)
{
	//cycle through the items, if found decrease quantity
	for(auto& it : this->items)
	{
		if(it.first == item)
		{
			it.second -= count;
		}
		//iterate through the list again, if the lambda function returns an element
		//it if removed by the remove_if algorithm
		this->items.remove_if([](std::pair<Item*, int>& element)
		{
			return element.second < 1;
		});
	}
}

void Inventory::remove_weapon(Weapon*, int count)
{
	//cycle through the items, if found decrease quantity
	for(auto& it : this->weapons)
	{
		if(it.first == weapon)
		{
			it.second -= count;
		}
		//iterate through the list again, if the lambda function returns an element
		//it if removed by the remove_if algorithm
		this->items.remove_if([](std::pair<Weapon*, int>& element)
		{
			return element.second < 1;
		});
	}
}

void Inventory::remove_armour(Armour*, int count)
{
	//cycle through the items, if found decrease quantity
	for(auto& it : this->armour)
	{
		if(it.first == armour)
		{
			it.second -= count;
		}
		//iterate through the list again, if the lambda function returns an element
		//it if removed by the remove_if algorithm
		this->items.remove_if([](std::pair<Armour*, int>& element)
		{
			return element.second < 1;
		});
	}
}

//merge the specified Inventory with the current one
//adding item quantaties if they exist, creating a new slot if they don't
void Inventory::merge(Inventory* inventory)
{
	//you can't merge with itself
	if(inventory == this)
	{
		return;
	}
	//loop through the items and add them
	for(auto it: inventory->items)
	{
		this->add_item(it.first, it.second);
	}
	for(auto it: inventory->weapons)
	{
		this->add_weapon(it.first, it.second);
	}
	for(auto it: inventory->armour)
	{
		this->add_armour(it.first, it.second);
	}
	return;
}

void Inventory::clear()
{
	this->items.clear();
	this->weapons.clear();
	this->armour.clear();
}

//output a list of items to stdout, nicely formatted
int Inventory::print_items(bool label = false)
{
	unsigned int i = 1;

	for(auto it : this->items)
	{
		//number items if asked
		if(label)
		{
			std::cout << i++ << ":";
			//output the item name, quantity and description
			std::cout << it.first->name << " (" << it.second << ") - ";
			std::cout <<it.first->description << std::endl;
		}
		//return number of items outputted, for convienience
		return this->items.size();
	}
}

//output a list of weapons to stdout, nicely formatted
int Inventory::print_weapons(bool label = false)
{
	unsigned int i = 1;

	for(auto it : this->weapons)
	{
		//number items if asked
		if(label)
		{
			std::cout << i++ << ":";
			//output the item name, quantity and description
			std::cout << it.first->name << " (" << it.second << ") - ";
			std::cout <<it.first->description << std::endl;
		}
		//return number of items outputted, for convienience
		return this->weapons.size();
	}
}

//output a list of armour to stdout, nicely formatted
void Inventory::print_armour(bool label = false)
{
	unsigned int i = 1;

	for(auto it : this->armour)
	{
		//number items if asked
		if(label)
		{
			std::cout << i++ << ":";
			//output the item name, quantity and description
			std::cout << it.first->name << " (" << it.second << ") - ";
			std::cout <<it.first->description << std::endl;
		}
		//return number of items outputted, for convienience
		return this->armour.size();
	}
}

//print the entire inventory, unless it is empty
int Inventory::print(bool = false)
{
	if(this->items.size() == 0 && 
		this->weapons.size() == 0 &&
		this->armour.size() == 0)
	{
		std::cout << "Empty!" << std::endl;
	}
	else
	{
		this->print_items(label);
		this->print_weapons(label);
		this->print_armour(label);
	}
	return;
}
#endif //INVENTORY_HPP