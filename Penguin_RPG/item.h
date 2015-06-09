#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
public:
	Item(){};
	Item(std::string name, std::string description) :
		name(name), description(description){};

	//name and description of item
	std::string name;
	std::string description;
};
#endif //ITEM_H