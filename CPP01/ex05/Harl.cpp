#include "Harl.hpp"

Harl::Harl()
{
    levelFunctions["debug"] = &Harl::debug;
    levelFunctions["info"] = &Harl::info;
    levelFunctions["warning"] = &Harl::warning;
    levelFunctions["error"] = &Harl::error;
}

Harl::~Harl() {}

Harl &Harl::operator= (const Harl &object)
{
	if (this != &object)
		this->levelFunctions = object.levelFunctions;

	return *this;
}

void Harl::debug()
{
	std::cout << "Debug" << std::endl;
}

void Harl::info()
{
	std::cout << "Info" << std::endl;
}

void Harl::warning()
{
	std::cout << "Warning" << std::endl;
}

void Harl::error()
{
	std::cout << "Error" << std::endl;
}

void Harl::complain(std::string level)
{
    if (levelFunctions.find(level) != levelFunctions.end())
        (this->*levelFunctions[level])();
    else
        std::cout << "Invalid level: " << level << std::endl;
}
