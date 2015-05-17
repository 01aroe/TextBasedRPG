#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <cstdlib>
#include <ctime>

#include "area.hpp"
#include "armour.hpp"
#include "atlas.hpp"
#include "battle.hpp"
#include "creature.hpp"
#include "dialogue.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "weapon.hpp"

Creature dialogue_newChar();
void dialogue_menu(Creature& player);

int main(void)
{
	std::vector<Creature> creatureAtlas;
	std::vector<Item> itemAtlas;
	std::vector<Weapon> weaponAtlas;
	std::vector<Armour> armourAtlas;
	std::vector<Area> areaAtlas;

	// Build the atlases
	buildatlas_creature(creatureAtlas);
	buildatlas_item(itemAtlas);
	buildatlas_weapon(weaponAtlas);
	buildatlas_armours(armourAtlas);
	buildatlas_area(areaAtlas, itemAtlas, weaponAtlas,
		armourAtlas, creatureAtlas);

	Creature player;

	//seed rand() with system time, to produce better random numbers
	srand(time(NULL));

	//main game menu dialogue
	int result = Dialogue("Welcome to the jungle!", { "New Game" }).activate();

	switch (result)
	{
	case 1:
		player = dialogue_newChar();
		break;
	default:
		return 0;
		break;
	}
	// Set the current area to be the first area in the atlas,
	// essentially placing the player there upon game start
	Area* currentArea = &(areaAtlas[0]);

	// Play the game until a function breaks the loop and closes it
	while (1)
	{
		// If the player has died then inform them as such and close
		// the program
		if (player.health <= 0)
		{
			std::cout << "\t----YOU DIED----\n    Game Over\n";
			return 0;
		}

		// If the area the player is in has any creatures inside it,
		// then begin a battle with the last creature in the list
		// before moving on the next one. This makes the creature
		// list act like a stack
		if (currentArea->creatures.size() > 0)
		{
			for (int i = currentArea->creatures.size() - 1; i >= 0; --i)
			{
				Battle(&player, currentArea->creatures[i]).run();
				// Remove the creature from the area. This is fine to do
				// because if the player wins the creature will not respawn,
				// and if the creature wins the player isn't around to see it
				// (This does break the 'non-mutable' feature of the atlases,
				// but doing so saves a lot of memory, as we don't need to keep
				// two versions of each area)
				currentArea->creatures.pop_back();
			}
		}

		// Activate the current area's dialogue
		result = currentArea->dialogue.activate();

		// These could be moved inside of the area code using an
		// event style system, but that allows for much less
		// flexibility with what happens in each area. Since we're
		// defining the areas in code anyway, sticking with this
		// isn't too much of a problem, and it keeps things easy
		// to understand
		if (currentArea == &(areaAtlas[0]))
		{
			switch (result)
			{
			case 1:
				// Move to area 1
				currentArea = &(areaAtlas[1]);
				break;
			case 2:
				// Search the area
				currentArea->search(player);
				break;
			default:
				break;
			}
		}
		else if (currentArea == &(areaAtlas[1]))
		{
			switch (result)
			{
			case 1:
				// Move to area 2
				currentArea = &(areaAtlas[2]);
				break;
			case 2:
				// Search the area
				currentArea->search(player);
				break;
			default:
				break;
			}
		}
		else if (currentArea == &(areaAtlas[2]))
		{
			switch (result)
			{
				// Move to area 0
			case 1:
				currentArea = &(areaAtlas[0]);
				break;
				// Search the area
			case 2:
				currentArea->search(player);
				break;
			default:
				break;
			}
		}
	}

	return 0;

}

//create a new character
Creature dialogue_newChar()
{
	//ask for a name and class
	std::cout << "Choose your name punk!" << std::endl;
	std::string name;
	std::cin >> name;

	int result = Dialogue("Choose your class!", { "Fighter", "Rogue" }).activate();

	switch (result)
	{
	case 1:
		//Fighter favours health and strength
		return Creature(name, 35, 20, 10, 5, 10.0, 1, "Fighter");
		break;
	case 2:
		//Rogue favours endurance and dexterity
		return Creature(name, 30, 5, 10, 20, 15.0, 1, "Rogue");
		break;
	default:
		//default should not happen, good to be safe though!
		return Creature(name, 30, 10, 10, 10, 10.0, 1, "Adventurer");
		break;
	}
}

void dialogue_menu(Creature& player)
{
	//Output the menu
	int result = Dialogue(
		"Menu\n====",
		{ "Items", "Equiptment", "Character" }).activate();

	return;
}