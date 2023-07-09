#include "Zombie.hpp"

//void a()
//{
//	system("leaks ex00");
//}

int	main()
{
	Zombie *zombie1 = newZombie("Zombie1");
	Zombie zombie("Zombie2");
	Zombie zombie2(zombie);
	zombie2.announce();
	delete zombie1;
	
	randomChump("Zombie3");
	//atexit(a);
}