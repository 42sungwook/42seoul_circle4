#ifndef HARL_HPP
#define HARL_HPP

#include <iostream>
#include <functional>
#include <map>
#include <algorithm> // for std::transform
#include <cctype>		 // for std::tolower

class Harl
{
private:
	std::map<std::string, void (Harl::*)()> levelFunctions;

	void debug();
	void info();
	void warning();
	void error();

public:
	Harl();
	~Harl();
	Harl &operator=(const Harl &object);
	void complain(std::string level);
};

#endif
