#include "Zombie.hpp"

//void a()
//{
//	system("leaks ex01");
//}

int	main()
{
	Zombie *zombie = zombieHorde(1, "ZombieA");
	delete [] zombie;
	Zombie *zombie2 = zombieHorde(2, "ZombieB");
	delete [] zombie2;
	Zombie *zombie3 = zombieHorde(0, "ZombieC");
	delete [] zombie3;
	//atexit(a);
}