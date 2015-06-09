#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <cstdlib>
#include <ctime>

#include "area.h"
#include "armour.h"
#include "atlas.h"
#include "battle.h"
#include "creature.h"
#include "dialogue.h"
#include "inventory.h"
#include "item.h"
#include "weapon.h"

void game_complete();
Creature dialogue_newChar();
void dialogue_menu(Creature& player);

int main(void)
{
	std::vector<Creature> creatureAtlas;
	std::vector<Item> itemAtlas;
	std::vector<Healing> healingAtlas;
	std::vector<Weapon> weaponAtlas;
	std::vector<Armour> armourAtlas;
	std::vector<Area> areaAtlas;

	// Build the atlases
	buildatlas_creature(creatureAtlas);
	buildatlas_item(itemAtlas);
	buildatlas_healing(healingAtlas);
	buildatlas_weapon(weaponAtlas);
	buildatlas_armours(armourAtlas);
	buildatlas_area(areaAtlas, itemAtlas, healingAtlas,
		weaponAtlas, armourAtlas, creatureAtlas);

	Creature player;

	//seed rand() with system time, to produce better random numbers
	srand(time(nullptr));

	//main game menu dialogue
	int result = Dialogue
		("***********************\n*                     *\n*      FIGHT CLUB     *\n*                     *\n***********************\n",
		{ "New Game" }).activate();

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
			std::cout << "---- YOU DIED ----\n";
			std::cout << "---- GAME OVER ----\n";
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
				dialogue_menu(player);
				break;
			case 2:
				// Move to area 1
				currentArea = &(areaAtlas[1]);
				break;
			case 3:
				// Search the area
				currentArea->search(player);
				break;
			case 4:
				// Exit Game
				return 0;
			default:
				break;
			}
		}
		else if (currentArea == &(areaAtlas[1]))
		{
			switch (result)
			{
			case 1:
				dialogue_menu(player);
				break;
			case 2:
				// Move to area 2
				currentArea = &(areaAtlas[2]);
				break;
			case 3:
				// Search the area
				currentArea->search(player);
				break;
			case 4:
				// Exit game
				return 0;
			default:
				break;
			}
		}
		else if (currentArea == &(areaAtlas[2]))
		{
			switch (result)
			{
			case 1:
				dialogue_menu(player);
				break;
			case 2:
				// Move to area 3
				currentArea = &(areaAtlas[3]);
				break;
			case 3:
				currentArea->search(player);
				break;
			case 4:
				// Search the area
				return 0;
			default:
				break;
			}
		}
		else if (currentArea == &(areaAtlas[3]))
		{
			switch (result)
			{
			case 1:
				dialogue_menu(player);
				break;

			case 2:
				// Move to area 4
				currentArea = &(areaAtlas[4]);
				break;
			case 3:
				currentArea->search(player);
				break;
			case 4:
				return 0;
			default:
				break;
			}
		}
		else if (currentArea == &(areaAtlas[4]))
		{
			switch (result)
			{
			case 1:
				dialogue_menu(player);
				break;
			case 2:
				currentArea = &(areaAtlas[5]);
				break;
				// Move to area 5
			case 3:
				currentArea->search(player);
				break;
			case 4:
				// Search the area
				return 0;
			default:
				break;
			}
		}
		else if (currentArea == &(areaAtlas[5]))
		{
			switch (result)
			{
			case 1:
				dialogue_menu(player);
				break;

			case 2:
				// Move to area 6
				currentArea = &(areaAtlas[6]);
				break;
			case 3:
				currentArea->search(player);
				break;
			case 4:
				return 0;
			default:
				break;
			}
		}
		else if (currentArea == &(areaAtlas[6]))
		{
			game_complete();
			return 0;
		}
	}
	return 0;
}

void game_complete()
{
	std::cout << "you have completed the game motherfucker";
}

//create a new character
Creature dialogue_newChar()
{
	//ask for a name and class
	std::cout << "Enter your fighters name:" << std::endl;
	std::string name;
	std::cin >> name;

	int result = Dialogue("Choose your class:", { "Fighter", "Rogue" }).activate();

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
		"**** MENU **** \n\n",
		{ "Items", "Equiptment", "Character" }).activate();

	switch (result)
	{
		//Print the items that the player owns
	case 1:
		std::cout << "**** ITEMS ****\n\n";
		player.inventory.print();
		break;
		//Print the equiptment the player is wearing, then ask if they want 
		//to equip any of them
	case 2:
	{
		std::cout << "**** EQUIPTMENT ****\n\n";
		std::cout << "Head "
			<< (player.equippedArmour[Armour::Slot::HEAD] != nullptr ?
			player.equippedArmour[Armour::Slot::HEAD]->name : "Nothing")
			<< std::endl;
		std::cout << "Torso "
			<< (player.equippedArmour[Armour::Slot::TORSO] != nullptr ?
			player.equippedArmour[Armour::Slot::TORSO]->name : "Nothing")
			<< std::endl;
		std::cout << "Legs "
			<< (player.equippedArmour[Armour::Slot::LEGS] != nullptr ?
			player.equippedArmour[Armour::Slot::LEGS]->name : "Nothing")
			<< std::endl;
		std::cout << "Weapon "
			<< (player.equippedWeapon != nullptr ?
			player.equippedWeapon->name : "Nothing")
			<< std::endl;

		int result2 = Dialogue(
			"", { "Use Healing","Equip Armour", "Equip Weapon", "Close Menu" }).activate();
		//Equipping Armour
		if (result2 == 1)
		{
			int userInput = 0;

			//Cannot use if they do not have healing
			//Print and retrive a list of healing
			int numItems = player.inventory.print_healing(true);
			if (numItems == 0)
			{
				break;
			}
			while (!userInput)
			{
				//Choose healing to use
				std::cout << "Use which item?\n";
				std::cin >> userInput;

				//Equiptment is numbered but stored in a list
				//Must be converted into a list element
				if (userInput >= 1 && userInput <= numItems)
				{
					int i = 1;

					for (auto it : player.inventory.healing)
					{
						if (i++ == userInput)
						{
							//Use healing if it is found
							player.equipHealing(it.first);
							break;
						}
					}
				}
			}
		}
		if (result2 == 2)
		{
			int userInput = 0;

			//Cannot equip if they do not have armour
			//Print and retrive a list of armour
			int numItems = player.inventory.print_armours(true);
			if (numItems == 0)
			{
				break;
			}
			while (!userInput)
			{
				//Choose Armour to equip
				std::cout << "Equip which item?\n";
				std::cin >> userInput;

				//Equiptment is numbered but stored in a list
				//Must be converted into a list element
				if (userInput >= 1 && userInput <= numItems)
				{
					int i = 1;

					for (auto it : player.inventory.armours)
					{
						if (i++ == userInput)
						{
							//Equip armour if it is found
							player.equipArmour(it.first);
							break;
						}
					}
				}
			}
		}
		//Do the same for weapons
		else if (result2 == 3)
		{
			int userInput = 0;

			//Cannot equip if they do not have armour
			//Print and retrive a list of armour
			int numItems = player.inventory.print_weapons(true);
			if (numItems == 0)
			{
				break;
			}
			while (!userInput)
			{
				//Choose Armour to equip
				std::cout << "Equip which item?" << std::endl;
				std::cin >> userInput;

				//Equiptment is numbered but stored in a list
				//Must be converted into a list element
				if (userInput >= 1 && userInput <= numItems)
				{
					int i = 1;

					for (auto it : player.inventory.weapons)
					{
						if (i++ == userInput)
						{
							//Equip armour if it is found
							player.equipWeapon(it.first);
							break;
						}
					}
				}
			}
		}
		std::cout << "\n\n";
		break;
	}
	//Output the character info, including name, class, stats, level and exp
	case 3:
		std::cout << "**** CHARACTER ****\n\n";
		std::cout << player.name;
		if (player.className != "")
		{
			std::cout << " the " << player.className;
		}
		std::cout << std::endl;

		std::cout << "HP: " << player.health << " / " << player.maxHealth << std::endl;
		std::cout << "Str: " << player.str << std::endl;
		std::cout << "End: " << player.end << std::endl;
		std::cout << "Dex: " << player.dex << std::endl;
		std::cout << "Lvl: " << player.level << " (" << player.experience;
		std::cout << " / " << player.expToLevel(player.level + 1) << ")" << std::endl;
		std::cout << "\n\n";
		break;
	default:
		break;
	}
	return;
}