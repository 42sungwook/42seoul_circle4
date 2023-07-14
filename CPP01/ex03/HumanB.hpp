#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"

class HumanB
{
private:
	std::string _name;
	Weapon *_weapon;

public:
	HumanB(const std::string &name);
	~HumanB();
	HumanB &operator=(const HumanB &name);
	HumanB(const HumanB &object);
	void attack(void) const;
	void setWeapon(Weapon &weapon);
};

#endif
