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
						<< "\n"
						<< std::endl;
}

void Harl::complain(std::string level)
{
	if (levelFunctions.find(level) != levelFunctions.end())
		(this->*levelFunctions[level])();
	else
		std::cout << "[" << level << "]"
							<< "\n"
							<< "This level is invalid!"
							<< "\n"
							<< std::endl;
}
