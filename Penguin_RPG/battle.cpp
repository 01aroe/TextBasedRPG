#include "battle.h"

void Battle::attack(Creature* a, Creature* b)
{
	std::cout << "	" << a->name << " attacks" << std::endl;

	//Damage that will do to b
	int damage = 0;

	//Cumulative modifier to hitRate
	double hitRate = a->hitRate;

	// If a has equipped a weapon, then add the weapon damage on
	// to the current damage and add the hit rate of the weapon on to
	// the current hit rate
	if (a->equippedWeapon != nullptr)
	{
		damage += a->equippedWeapon->damage;
		hitRate += a->equippedWeapon->hitRate;
	}
	//Increase the damage by half the attackers strength
	damage += (a->str / 2);

	//Damage that b will block
	int defence = 0;

	// Sum the defense values of the armour that b has equipped, and
	// increase the defense by the summed value
	for (int i = 0; i < Armour::Slot::N; ++i)
	{
		if (b->equippedArmour[i] != nullptr)
		{
			defence += b->equippedArmour[i]->defence;
		}
	}

	// Decrease the damage by the damage blocked, then ensure that
	// damage is always inflicted (we do not want battles to last
	// forever, nor to we want attacks to heal the wounded!)
	damage -= defence;
	if (damage < 1)
	{
		damage = 1;
	}

	// Add the hit rate to the base hit rate and subract the target's
	// dexterity from it. Instead of halving it to normalise it into
	// a percentage, we just double the range of randomly generated
	// values
	if (rand() % 201 <= 170 + hitRate - b->dex)
	{
		//The attack hit, so subtract the damage
		std::cout << "		" << b->name << " takes " << damage << " damage! " << std::endl;
		b->health -= damage;
	}
	else
	{
		//The attack missed
		std::cout << "		" << a->name << " missed!" << std::endl;
	}
	return;
}
void Battle::playerTurn()
{
	// Activate the dialogue and allow the player to choose their
	// battle option
	int result = this->dialogue.activate();

	switch (result)
	{
		//Attack the enemy
	case 1:
		attack(creatures[0], creatures[1]);
		break;
		//Defend, skipping to enemy's turn
	case 2:
		std::cout << "	" << creatures[0]->name << " defends" << std::endl;
		break;
	default:
		break;
	}
	return;
}

void Battle::enemyTurn()
{
	// Battle system does not currently allow for any kind of
	// tactics, so make the enemy attack blindly
	attack(creatures[1], creatures[0]);
	return;
}
bool Battle::isDead(Creature* creature)
{
	// Return true if the creature is dead. Split into it's own function
	// to allow easy addition of effects which simulate death, such as
	// petrifaction or banishment
	if (creature->health <= 0)
	{
		return true;
	}
	return false;
}
bool Battle::activate()
{
	// The creature with the highest dexterity attacks first, with
	// preference to the player
	if (creatures[0]->dex >= creatures[1]->dex)
	{
		// Run each turn and check if the foe is dead at the end of
		// each
		this->playerTurn();
		if (isDead(creatures[1]))
		{
			std::cout << "			" << creatures[1]->name << " was destroyed!!\n";
			return true;
		}
		this->enemyTurn();
		if (isDead(creatures[0]))
		{
			std::cout << "			" << creatures[0]->name << " was destroyed!!\n";
			return true;
		}
	}
	else
	{
		this->enemyTurn();
		if (isDead(creatures[0]))
		{
			std::cout << "			" << creatures[0]->name << " was destroyed!!\n";
			return true;
		}

		this->playerTurn();
		if (isDead(creatures[1]))
		{
			std::cout << "			" << creatures[1]->name << " was destroyed!!\n";
			return true;
		}
	}
	return false;
}
void Battle::run()
{
	std::cout << "\n" << creatures[1]->name << " appears" << std::endl;

	//Run the battle until one dies
	while (!this->activate());

	// If the enemy is dead, then allocate experience to
	// the player
	if (isDead(creatures[1]))
	{
		// Give experience to the player equal to one eigth
		// of the experience the enemy gained to reach its
		// next level
		unsigned int expGain = creatures[1]->expToLevel(creatures[1]->level + 1) / 8;
		std::cout << "				" << "Gained " << expGain << " exp!" << std::endl;
		creatures[0]->experience += expGain;

		// Repeatedly level up the player until they are the highest
		// level they can be for their experience
		while (creatures[0]->levelUp());
	}
	return;
}