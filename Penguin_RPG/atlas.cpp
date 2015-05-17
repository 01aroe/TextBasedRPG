#include "atlas.hpp"

void buildatlas_creature(std::vector<Creature>& atlas)
{
	//fill the atlas
	//Creature(name, health, str, end, dex, hitRate, level)
	atlas.push_back(Creature("Iron Man", 4, 2, 8, 9, 1.0, 1));
	atlas.push_back(Creature("Captain America", 8, 8, 8, 12, 2.0, 2));
	atlas.push_back(Creature("The Hulk", 12, 16, 8, 4, 1.5, 3));
	
	return;
}
void buildatlas_item(std::vector<Item>& atlas)
{
	//Item(name, description)
	atlas.push_back(Item("Gold Coin",
		"A small disc made of lustrous metal"));
	atlas.push_back(Item("Iron Key",
		"A heavy iron key with a simple cut"));
	atlas.push_back(Item("Med Pack",
		"A small bag with items to heal"));
	atlas.push_back(Item("Holy Water",
		"The finest of all water...it does nothing"));

	return;
}
void buildatlas_weapon(std::vector<Weapon>& atlas)
{
	//Weapon(name, description, damage, hitRate)
	atlas.push_back(Weapon("Iron Dagger",
		"A short blade made of iron with a leather hilt",
		5, 10.0));
	atlas.push_back(Weapon("Excalibur",
		"The legendary blade, bestowed upon you by the lady of the lake",
		35, 35.0));
	atlas.push_back(Weapon("Machete",
		"A large bladed knife used by rebels",
		50, 40.0));

	return;
}
void buildatlas_armours(std::vector<Armour>& atlas)
{
	//Armour(name, description, defence, slot)
	atlas.push_back(Armour("Leather Vest",
		"Torso armour made of tanned hide",
		4, Armour::Slot::TORSO));
	atlas.push_back(Armour("Helemt",
		"Head armour made of tin",
		6, Armour::Slot::HEAD));
	atlas.push_back(Armour("Kevlar Pants",
		"Leg armour made of super tough kevlar",
		12, Armour::Slot::LEGS));

	return;
}
void buildatlas_area(std::vector<Area>& atlas,
	std::vector<Item>& items, std::vector<Weapon>& weapons,
	std::vector<Armour>& armours, std::vector<Creature>& creatures)
{
	// Area definitions are somewhat more complicated:
	atlas.push_back(Area(Dialogue(        // Standard dialogue definiton
		"You are in the main hall",              // Description
		{ "Go to the back room", "Search the room" }),      // Choices
		Inventory(                        // Area inventory
	{
		std::make_pair(&items[0], 5)  // Pair of item and quantity
	},
	{
		std::make_pair(&weapons[0], 2) // Pair of weapon and quantity
	},
	{
		std::make_pair(&armours[0], 3) // Pair of armour and quantity
	}),
	{    
		&creatures[0] // Creatures
	}));

	atlas.push_back(Area(Dialogue(
		"You are in the back room",
		{ "Go to the vault", "Search the room" }),
		Inventory(
	{
		std::make_pair(&items[2], 5)
	},
	{
		std::make_pair(&weapons[1], 2)
	},
	{
		std::make_pair(&armours[1], 3)
	}),
	{
		&creatures[1] // Creatures
	}));

	atlas.push_back(Area(Dialogue(
		"You are in the vault",
		{ "Go to the main hall", "Search the room" }),
		Inventory(
	{
		std::make_pair(&items[3], 5)
	},
	{
		std::make_pair(&weapons[2], 1)
	},
	{
		std::make_pair(&armours[2], 2)
	}),
	{
		&creatures[2] // Creatures
	}));

	return;
}