#include "HumanA.hpp"

HumanA::HumanA(const std::string& name, Weapon& weapon): _name(name), _weapon(weapon){}

HumanA::~HumanA() {}

HumanA &HumanA::operator= (const HumanA &name) {
	_name = name._name;
	_weapon = name._weapon;
	return (*this);
}

HumanA::HumanA(const HumanA &object): _weapon(object._weapon){
	*this = object;
}

void HumanA::attack(void) const {
	std::cout << _name << " attacks with his " << _weapon.getType() << std::endl;
}
