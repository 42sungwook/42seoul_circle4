#include "HumanB.hpp"

HumanB::HumanB(const std::string& name): _name(name){}

HumanB::~HumanB() {}

HumanB &HumanB::operator= (const HumanB &name) {
	_name = name._name;
	return (*this);
}

HumanB::HumanB(const HumanB &object){
	*this = object;
}

void HumanB::attack(void) const {
	std::cout << _name << " attacks with his " << _weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon& weapon) {
	_weapon = &weapon;
}
