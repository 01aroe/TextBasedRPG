#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <cstdlib>
#include <ctime>

#include "dialogue.hpp"
#include "creature.hpp"

Creature dialogue_newChar();

int main(void)
{
	Creature player;

	//seed rand() with system time, to produce better random numbers
	srand(time(NULL));

	//main game menu dialogue
	//c++11 not supported in VS2010
	//int result = Dialogue("Welcome to the jungle!", { "New Game" }).activate();

	std::vector<std::string> state;
	state.push_back("New Game");
	int result = Dialogue("Welcome to the jungle!", state).activate();

		switch (result)
	{
		case 1:
			player = dialogue_newChar();
			break;
		default:
			return 0;
			break;
	}

	while(1)
	{
		//if the player has died, inform them and close
		if(player.health == 0)
		{
			std::cout << "\t------- FATALITY -------\n    GAME OVER!\n";
			return 0;
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

	//c++11 not supported in VS2010
	//int result = Dialogue("Choose your class!", {"Fighter", "Rogue"}).activate();

	//Old style list initialization
	std::vector<std::string> choices;
	choices.push_back("Fighter");
	choices.push_back("Rogue");
	int result = Dialogue("Choose your class", choices).activate();
	
	switch(result)
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