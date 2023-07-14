#include "Harl.hpp"

void Harl::debug()
{
	std::cout << "[DEBUG]"
						<< "\n"
						<< "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!"
						<< "\n"
						<< std::endl;
}

void Harl::info()
{
	std::cout << "[INFO]"
						<< "\n"
						<< "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!"
						<< "\n"
						<< std::endl;
}

void Harl::warning()
{
	std::cout << "[WARNING]"
						<< "\n"
						<< "I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month."
						<< "\n"
						<< std::endl;
}

void Harl::error()
{
	std::cout << "[ERROR]"
						<< "\n"
						<< "This is unacceptable! I want to speak to the manager now."
						<< "\n---------------------------------------------------------------------------------"
						<< std::endl;
}

void Harl::complain(std::string level)
{
	int levelCode = 0;
	const std::string levelStrings[] = {"debug", "info", "warning", "error"};
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
		std::cout << "[" << level << "]"
							<< "\n"
							<< "This level is invalid!"
							<< "\n---------------------------------------------------------------------------------"
							<< std::endl;
		break;
	}
}