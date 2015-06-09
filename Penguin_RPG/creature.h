#ifndef CREATURE_H
#define CREATURE_H

#include "inventory.h"
#include <string>

class Creature
{
public:
	Creature();
	Creature(std::string name, int health, int str, int end, int dex,
		double hitRate, unsigned int level = 1, std::string className = "");
	unsigned int expToLevel(unsigned int level);
	bool levelUp();

	void equipHealing(Healing* healing);
	void equipWeapon(Weapon* weapon);
	void equipArmour(Armour* armour);

	//name of the creature and name of the class/vocation
	std::string name;
	std::string className;

	//creature stats
	int health;
	int maxHealth;
	int str;
	int end;
	int dex;
	double hitRate;

	//current level of creature
	//determines the amount of exp given to the victor and 
	//exp required the level up. After levelling up stats will
	//increase. 0-50
	unsigned int level;

	//current exp. 0-1M
	unsigned int experience;

	//items that the creature possess
	Inventory inventory;

	//equipped weapon. Used as a ptr to an atlas entry but
	//not necessary. nullptr means no weapon equipped
	Weapon* equippedWeapon;

	//arour currently equipped in each slot
	Armour* equippedArmour[Armour::Slot::N];
};
#endif //CREATURE_H