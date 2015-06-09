#include "inventory.h"

//add an item to the inventory
void Inventory::add_item(Item* item, int count)
{
	// Increase the quantity if the item already exists
	for (auto& it : this->items)
	{
		if (it.first == item) it.second += count;
		return;
	}
	// If the item doesn't already exist in the inventory, then a
	// pair must be created too
	this->items.push_back(std::make_pair(item, count));
}

void Inventory::add_healing(Healing* healing, int count)
{
	for (auto& it : this->healing)
	{
		if (it.first == healing)
		{
			it.second += count;
			return;
		}
	}
	this->healing.push_back(std::make_pair(healing, count));
}

void Inventory::add_weapon(Weapon* weapon, int count)
{
	for (auto& it : this->weapons)
	{
		if (it.first == weapon)
		{
			it.second += count;
			return;
		}
	}
	this->weapons.push_back(std::make_pair(weapon, count));
}

void Inventory::add_armour(Armour* armour, int count)
{
	for (auto& it : this->armours)
	{
		if (it.first == armour)
		{
			it.second += count;
			return;
		}
	}
	this->armours.push_back(std::make_pair(armour, count));
}

void Inventory::remove_item(Item* item, int count)
{
	// Iterate through the items, and if they are found then decrease
	// the quantity by the quantity removed
	for (auto& it : this->items)
	{
		if (it.first == item) it.second -= count;
	}
	// Iterate through the list again, and remove any elements from
	// the list that have zero or less for their quantity
	// We do this in two passes because removing an element from
	// a list during a for loop invalidates the iterators, and the
	// loop stops working
	this->items.remove_if([](std::pair<Item*, int>& element)
	{
		return element.second < 1;
	});
}

void Inventory::remove_healing(Healing* healing, int count)
{
	for (auto& it : this->healing)
	{
		if (it.first == healing) it.second -= count;
	}
	this->healing.remove_if([](std::pair<Healing*, int>& element)
	{
		return element.second < 1;
	});
}

void Inventory::remove_weapon(Weapon* weapon, int count)
{
	for (auto& it : this->weapons)
	{
		if (it.first == weapon) it.second -= count;
	}
	this->weapons.remove_if([](std::pair<Weapon*, int>& element)
	{
		return element.second < 1;
	});
}

void Inventory::remove_armour(Armour* armour, int count)
{
	for (auto& it : this->armours)
	{
		if (it.first == armour) it.second -= count;
	}
	this->armours.remove_if([](std::pair<Armour*, int>& element)
	{
		return element.second < 1;
	});
}

//merge the specified Inventory with the current one
//adding item quantaties if they exist, creating a new slot if they don't
void Inventory::merge(Inventory* inventory)
{
	// You can't merge an inventory with itself!
	if (inventory == this) return;

	// Loop through the items to be added, and add them. Our addition
	// function will take care of everything else for us
	if (inventory != nullptr)
	{
		for (auto it : inventory->items)
		{
			this->add_item(it.first, it.second);
		}

		// Do the same for the healing
		for (auto it : inventory->healing)
		{
			this->add_healing(it.first, it.second);
		}

		// Do the same for the weapons
		for (auto it : inventory->weapons)
		{
			this->add_weapon(it.first, it.second);
		}
		// Do the same for the armour
		for (auto it : inventory->armours)
		{
			this->add_armour(it.first, it.second);
		}
	}
	return;
}

void Inventory::clear()
{
	this->items.clear();
	this->healing.clear();
	this->weapons.clear();
	this->armours.clear();
}

//output a list of items to stdout, nicely formatted
int Inventory::print_items(bool label)
{
	unsigned int i = 1;

	for (std::list<std::pair<Item*, int>>::iterator it =
		this->items.begin(); it != this->items.end(); ++it)
	{
		//number items if asked
		if (label)
		{
			std::cout << i++ << ":";
		}
		//output the item name, quantity and description
		std::cout << "	" << it->first->name << " (" << it->second << ") - ";
		std::cout << it->first->description << std::endl;

	}
	//return number of items outputted, for convienience
	return this->items.size();
}

//output a list of weapons to stdout, nicely formatted
int Inventory::print_healing(bool label)
{
	unsigned int i = 1;

	for (auto it : this->healing)
	{
		if (label)
		{
			std::cout << i++ << ": ";
		}
		std::cout << "	" << it.first->name << " (" << it.second << ") - ";
		std::cout << it.first->description << std::endl;
	}
	return this->healing.size();
}

//output a list of weapons to stdout, nicely formatted
int Inventory::print_weapons(bool label)
{
	unsigned int i = 1;

	for (auto it : this->weapons)
	{
		if (label)
		{
			std::cout << i++ << ": ";
		}
		std::cout << "	" << it.first->name << " (" << it.second << ") - ";
		std::cout << it.first->description << std::endl;
	}
	return this->weapons.size();
}

//output a list of armour to stdout, nicely formatted
int Inventory::print_armours(bool label)
{
	unsigned int i = 1;

	for (std::list<std::pair<Armour*, int>>::iterator it =
		this->armours.begin(); it != this->armours.end(); ++it)
	{
		//number items if asked
		if (label)
		{
			std::cout << i++ << ":";
		}
		//output the item name, quantity and description
		std::cout << "	" << it->first->name << " (" << it->second << ") - ";
		std::cout << it->first->description << std::endl;

	}
	//return number of items outputted, for convienience
	return this->armours.size();
}

//print the entire inventory, unless it is empty
void Inventory::print(bool label)
{
	if (this->items.size() == 0 &&
		this->healing.size() == 0 &&
		this->weapons.size() == 0 &&
		this->armours.size() == 0)
	{
		std::cout << "Nothing to see here!" << std::endl;
	}
	else
	{
		this->print_items(label);
		this->print_healing(label);
		this->print_weapons(label);
		this->print_armours(label);
	}
	return;
}