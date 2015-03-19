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
};

#endif //WEAPON_HPP