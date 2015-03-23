#pragma once

#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include <string>
#include <vector>
#include <iostream>

// Gameplay is expressed using dialogues, which present a piece of
// information and some responses, and they ask the user to pick one.
// If they do not pick a valid one then the dialogue loops until
// they do

class Dialogue
{
	//intial information to be displayed
	std::string description;
	//vector of choices
	std::vector<std::string> choices;
public:
	Dialogue(){};
	Dialogue(std::string description, std::vector<std::string> choices);
	int activate();
};

Dialogue::Dialogue(std::string description, std::vector<std::string> choices)
{
	this->description = description;
	this->choices = choices;
}

//run the dialogue
int Dialogue::activate()
{
	//output the information
	std::cout << description << std::endl;

	//output and number the choices
	for(unsigned int i = 0; i < this->choices.size(); i++)
	{
		std::cout << i+1 << ": " << this->choices[i] << std::endl;
	}

	int userInput = -1;

	//repeatedly read input from stdin until a valid option is chosen
	while(true)
	{
		std::cin >> userInput;

		//valid is within the range of numbers outputted
		if(userInput >= 0 && userInput <= this->choices.size())
		{
			return userInput;
		}
	}
	return 0;
}

#endif //DIALOGUE_HPP