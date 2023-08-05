#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap(), ScavTrap(), FragTrap()
{
	_energyPoints = scavTrapEnergyPoints;
	std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string &name) : ClapTrap(name), ScavTrap(name), FragTrap(name)
{
	_energyPoints = scavTrapEnergyPoints;
	std::cout << "DiamondTrap name constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &object)
{
	std::cout << "DiamondTrap copy constructor called" << std::endl;
	*this = object;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &object)
{
	std::cout << "DiamondTrap copy assignment operator called" << std::endl;
	_name = object._name;
	_hitPoints = object._hitPoints;
	_energyPoints = object._energyPoints;
	_attackDamage = object._attackDamage;
	return *this;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap destructor called" << std::endl;
}

void DiamondTrap::attack(const std::string &target)
{
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
	std::cout << "DiamondTrap name is " << _name << " and ClapTrap name is " << ClapTrap::getName() << std::endl;
}
