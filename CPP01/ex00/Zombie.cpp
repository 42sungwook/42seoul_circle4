#include "Zombie.hpp"

Zombie::Zombie(){}

Zombie::~Zombie() {
	std::cout << _name << ": NooooOOOooo..." << std::endl;
}

Zombie &Zombie::operator= (const Zombie &name) {
	_name = name._name;
	return (*this);
}

Zombie::Zombie(const std::string& name): _name(name){
	//std::cout << _name << ": Arrrrrrrrrrrrr..." << std::endl;
}

void Zombie::announce(void) const {
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}