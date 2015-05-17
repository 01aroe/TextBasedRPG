#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "dialogue.hpp"
#include "creature.hpp"
#include "armour.hpp"
#include "weapon.hpp"

#include <iostream>

class Battle
{
public:

	//Dialogue used to ask player battle choices
	Dialogue dialogue;

	//Creatures in combat. creatures[0] is the player
	Creature* creatures[2];

	Battle(){};
	Battle(Creature* player, Creature* opponent)
	{
		//Start a battle with the player and another creature
		this->creatures[0] = player;
		this->creatures[1] = opponent;

		//Set up the dialogue. Defending offers no advantage in this battle system
		this->dialogue = Dialogue("What will you do?", { "Attack", "Defend" });
	}
	void attack(Creature* a, Creature* b);
	void playerTurn();
	void enemyTurn();
	bool isDead(Creature* creature);
	bool activate();
	void run();

};

#endif BATTLE_HPP