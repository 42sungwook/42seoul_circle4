#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie
{
private:
	std::string _name;

public:
	Zombie();
	~Zombie();
	Zombie &operator=(const Zombie &name);
	Zombie(const Zombie &object);
	Zombie(const std::string &name);
	void announce(void) const;
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);

#endif