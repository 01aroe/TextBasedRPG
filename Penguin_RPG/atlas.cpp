#include "atlas.h"

void buildatlas_creature(std::vector<Creature>& atlas)
{
	//fill the atlas
	//Creature(name, health, str, end, dex, hitRate, level)
	atlas.push_back(Creature("Iron Man", 15, 5, 10, 6, 1.0, 3));
	atlas.push_back(Creature("Captain America", 20, 12, 4, 6, 1.5, 4));
	atlas.push_back(Creature("Storm", 25, 16, 8, 4, 3.0, 6));
	atlas.push_back(Creature("Hulk", 60, 30, 14, 8, 1.0, 8));
	atlas.push_back(Creature("Thor", 50, 25, 16, 10, 2.0, 10));
	atlas.push_back(Creature("Black Widow", 30, 8, 30, 25, 6.0, 12));
	atlas.push_back(Creature("Spider-Man", 35, 10, 8, 12, 5.0, 14));
	return;
}
void buildatlas_item(std::vector<Item>& atlas)
{
	//Item(name, description)
	atlas.push_back(Item("Iron Key",
		"A heavy iron key with a simple cut"));
	atlas.push_back(Item("Holy Water",
		"The finest of all water...it does nothing"));
	return;
}

void buildatlas_healing(std::vector<Healing>& atlas)
{
	atlas.push_back(Healing("Mini Heal",
		"A small medical kit that restores health",
		15));
	atlas.push_back(Healing("Massive Heal",
		"A large medical kit that restores health",
		40));
	return;
}

void buildatlas_weapon(std::vector<Weapon>& atlas)
{
	//Weapon(name, description, damage, hitRate)
	atlas.push_back(Weapon("Iron Dagger",
		"A short blade made of iron with a leather hilt",
		5, 10.0));
	atlas.push_back(Weapon("Machete",
		"A large bladed knife used by rebels",
		10, 15.0));
	return;
}
void buildatlas_armours(std::vector<Armour>& atlas)
{
	//Armour(name, description, defence, slot)
	atlas.push_back(Armour("Leather Vest",
		"Torso armour made of tanned hide",
		2, Armour::Slot::TORSO));
	atlas.push_back(Armour("Helemt",
		"Head armour made of tin",
		3, Armour::Slot::HEAD));
	atlas.push_back(Armour("Kevlar Pants",
		"Leg armour made of super tough kevlar",
		5, Armour::Slot::LEGS));
	return;
}
void buildatlas_area(std::vector<Area>& atlas,
	std::vector<Item>& items, std::vector<Healing>& healing,
	std::vector<Weapon>& weapons, std::vector<Armour>& armours,
	std::vector<Creature>& creatures)
{
	// Area definitions are somewhat more complicated:
	//Level 0 Atlas
	atlas.push_back(Area(Dialogue(        // Standard dialogue definiton
		"\nYou are deep within Stark Industries...",              // Description
		{ "Go to the North Atlantic", "Search the area", "Menu", "Exit" }),      // Choices
		Inventory(                        // Area inventory
	{
		std::make_pair(&items[1], 1)  // Pair of item and quantity
	},
	{
		std::make_pair(&healing[0], 1)//Pair of healing and quantity here
	},
	{
		std::make_pair(&weapons[0], 1) // Pair of weapon and quantity
	},
	{
		std::make_pair(&armours[0], 1) // Pair of armour and quantity
	}),
	{    
		&creatures[0] // Creatures
	}));

	//Level 1 Atlas
	atlas.push_back(Area(Dialogue(
		"\nYou are in the North Atlantic...",
		{ "Go to the X-Mansion", "Search the area", "Menu", "Exit" }),
		Inventory(
	{
		std::make_pair(&items[0], 1)
	},
	{
		//Pair of healing and quantity here
	},
	{
		std::make_pair(&weapons[1], 1)
	},
	{
		std::make_pair(&armours[1], 1)
	}),
	{
		&creatures[1] // Creatures
	}));

	//Level 2 Atlas
	atlas.push_back(Area(Dialogue(
		"\nYou are in the X-Mansion...",
		{ "Go to Dr. Banners Lab", "Search the area", "Menu", "Exit" }),
		Inventory(
	{
		std::make_pair(&items[0], 1)
	},
	{
		std::make_pair(&healing[1], 1)//Pair of healing and quantity here
	},
	{
	
	},
	{
		std::make_pair(&armours[2], 2)
	}),
	{
		&creatures[2] // Creatures
	}));

	//Level 3 Atlas
	atlas.push_back(Area(Dialogue(
		"\nYou are in Dr. Banners Lab...",
		{ "Go to Asgard", "Search the area", "Menu", "Exit" }),
		Inventory(
	{
		
	},
	{
		std::make_pair(&healing[0], 1) //Pair of healing and quantity here
	},
	{
	
	},
	{
		std::make_pair(&armours[2], 2)
	}),
	{
		&creatures[3] // Creatures
	}));

	//Level 4 Atlas
	atlas.push_back(Area(Dialogue(
		"\nYou are in Asgard...",
		{ "Go to the KGB Headquarters", "Search the area", "Menu", "Exit" }),
		Inventory(
	{
		std::make_pair(&items[1], 1)
	},
	{
		std::make_pair(&healing[0], 1)//Pair of healing and quantity here
	},
	{
		std::make_pair(&weapons[0], 1)
	},
	{
		std::make_pair(&armours[2], 2)
	}),
	{
		&creatures[4] // Creatures
	}));

	//Level 5 Atlas
	atlas.push_back(Area(Dialogue(
		"\nYou are in the KGB Headquarters...",
		{ "Go to the Daily Bugle", "Search the area", "Menu", "Exit" }),
		Inventory(
	{
		std::make_pair(&items[1], 5)
	},
	{
		std::make_pair(&healing[1], 1)//Pair of healing and quantity here
	},
	{
		
	},
	{
		std::make_pair(&armours[2], 2)
	}),
	{
		&creatures[5] // Creatures
	}));

	//Level 6 Atlas
	atlas.push_back(Area(Dialogue(
		"\nThe end is near...",
		{ "Go to End Credits", "Search the area", "Menu" }),
		Inventory(
	{
		std::make_pair(&items[0], 2)
	},
	{
		//Pair of healing and quantity here
	},
	{
		std::make_pair(&weapons[1], 1)
	},
	{
		std::make_pair(&armours[2], 2)
	}),
	{
		&creatures[6] // Creatures
	}));
	return;
}