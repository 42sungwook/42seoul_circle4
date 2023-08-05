#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int main()
{
	DiamondTrap diamondTrap("DiamondTrap");
	diamondTrap.attack("target");
	diamondTrap.guardGate();
	diamondTrap.highFivesGuys();
	diamondTrap.whoAmI();
	diamondTrap.getAttackDamage();
	std::cout << diamondTrap.getHitPoints() << std::endl;
	std::cout << diamondTrap.getEnergyPoints() << std::endl;
	std::cout << diamondTrap.getName() << std::endl;
	return 0;
}