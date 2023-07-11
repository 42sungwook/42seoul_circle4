#include "Harl.hpp"

Harl::Harl() {}

Harl::~Harl() {}

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
	int levelCode = 0;
	const std::string levelStrings[] = { "debug", "info", "warning", "error" };
	std::transform(level.begin(), level.end(), level.begin(), ToLower());

	for (int i = 0; i < LEVELS; ++i)
	{
		if (level == levelStrings[i])
		{
			levelCode = i + 1;
			break;
		}
	}

	switch (levelCode)
	{
		case 1:
			debug();
		case 2:
			info();
		case 3:
			warning();
		case 4:
			error();
			break;
		default:
			std::cout << "Invalid level: " << level << std::endl;
			break;
	}
}