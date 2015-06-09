#ifndef ATLAS_H
#define ATLAS_H

#include <vector>

#include "creature.h"
#include "item.h"
#include "healing.h"
#include "weapon.h"
#include "armour.h"
#include "area.h"

//atlas building functions. Atlases contain vectors of
//game data that is not modified. Could be replaced with
//functions that read from config files.

void buildatlas_creature(std::vector<Creature>& atlas);
void buildatlas_item(std::vector<Item>& atlas);
void buildatlas_healing(std::vector<Healing>& atlas);
void buildatlas_weapon(std::vector<Weapon>& atlas);
void buildatlas_armours(std::vector<Armour>& atlas);
void buildatlas_area(std::vector<Area>& atlas,
	std::vector<Item>& items, std::vector<Healing>& healing,
	std::vector<Weapon>& weapons, std::vector<Armour>& armours,
	std::vector<Creature>& creatures);

#endif //ATLAS_H