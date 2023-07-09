#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name) {
	Zombie *zombie = new Zombie[N];
	for (int i = 0; i < N; i++) {
		zombie[i].setName(name);
	}
	for (int i = 0; i < N; i++) {
		zombie[i].announce();
	}
	return (zombie);
}