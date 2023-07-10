#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"

class HumanA {
	private:
		std::string _name;
		Weapon&		_weapon;
	public:
		HumanA(const std::string& name, Weapon& weapon);
		~HumanA();
		HumanA &operator= (const HumanA &name);
		HumanA(const HumanA &object);
		void	attack(void) const;
};

#endif
