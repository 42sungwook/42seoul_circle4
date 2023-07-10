#include "Harl.hpp"

Harl::Harl()
{
    levelFunctions["debug"] = &Harl::debug;
    levelFunctions["info"] = &Harl::info;
    levelFunctions["warning"] = &Harl::warning;
    levelFunctions["error"] = &Harl::error;
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
    std::transform(level.begin(), level.end(), level.begin(), ToLower());

    if (levelFunctions.find(level) != levelFunctions.end())
        (this->*levelFunctions[level])();
    else
        std::cout << "Invalid level: " << level << std::endl;
}
