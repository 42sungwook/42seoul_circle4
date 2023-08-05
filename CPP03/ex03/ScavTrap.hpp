#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public virtual ClapTrap
{
public:
	unsigned int scavTrapEnergyPoints;

	ScavTrap();
	ScavTrap(const std::string &name);
	ScavTrap(const ScavTrap &object);
	ScavTrap &operator=(const ScavTrap &object);
	virtual ~ScavTrap();

	void guardGate();
	virtual void attack(const std::string &target);
};

#endif
