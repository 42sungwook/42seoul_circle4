#include "HumanB.hpp"

HumanB::HumanB(const std::string& name): _name(name){
	_weapon = NULL;
}

HumanB::~HumanB() {}

HumanB &HumanB::operator= (const HumanB &name) {
	_name = name._name;
	_weapon = name._weapon;
	return (*this);
}

HumanB::HumanB(const HumanB &object){
	*this = object;
}

void HumanB::attack(void) const {
	if (!_weapon)
	{
		std::cout << _name << " has no weapon" << std::endl;
		return ;
	}
	std::cout << _name << " attacks with his " << _weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon& weapon) {
	_weapon = &weapon;
}
