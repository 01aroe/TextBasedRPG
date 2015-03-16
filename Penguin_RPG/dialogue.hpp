//#ifndef DIALOGUE_HPP
//#define DIALOGUE_HPP

#include <string>
#include <vector>
#include <iostream>

// Gameplay is expressed using dialogues, which present a piece of
// information and some responses, and they ask the user to pick one.
// If they do not pick a valid one then the dialogue loops until
// they do

class Dialogue
{
public:
	Dialogue();
	Dialogue(std::string description, std::vector<std::string> choices)
	{
		this->description = description;
		this->choices = choices;
	}
private:
	//intial information to be displayed
	std::string description;
	//vector of choices
	std::vector<std::string> choices;
};

//#endif //DIALOGUE_HPP