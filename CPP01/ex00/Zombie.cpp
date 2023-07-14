#include "Zombie.hpp"

Zombie::Zombie(const std::string &name) : _name(name) {}

void Zombie::announce(void) const
{
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}