#ifndef ARMOUR_H
#define ARMOUR_H

#include "item.h"
#include <string>

//armour should also inherit item properties
class Armour : public Item
{
public:
	//armour goes into 1 of 3 slots, only 1 piece can occupy
	//each slot at a time. N is used to retrieve num of slots
	enum Slot { TORSO, HEAD, LEGS, N };
	Slot slot;

	//battle class for more detail, values 1-50 reasonable
	int defence;

	Armour(){};
	Armour(std::string name, std::string description, int defence,
		Slot slot) : Item(name, description), defence(defence), slot(slot) {};
};
#endif //ARMOUR_H