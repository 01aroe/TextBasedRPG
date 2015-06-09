#ifndef HEALING_H
#define HEALING_H

#include "item.h"
#include <string>

class Healing : public Item
{
public:
	Healing(){};
	Healing(std::string name, std::string description, unsigned int healing) :
		Item(name, description), healing(healing){};

	//Healing value
	unsigned int healing;

};
#endif //HEALING_H