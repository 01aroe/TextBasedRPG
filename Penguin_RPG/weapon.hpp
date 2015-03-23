#pragma once

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "item.hpp"
#include <string>

//Weapons are items, so they inherit their properties
class Weapon: public Item
{
public:
	Weapon(){};

	//weapon damage, battle class has formula
	//values between 1-50 reasonable
	unsigned int damage;

	//hit rate modifier, small values encouraged 5-30%
	double hitRate;

	Weapon(std::string name, std::string description,
		unsigned int damage, double hitRate);
};

Weapon::Weapon(std::string name, std::string description,
	unsigned int damage, double hitRate) : Item(name, description)
{
	this->damage = damage;
	this->hitRate = hitRate;
}

#endif //WEAPON_HPP