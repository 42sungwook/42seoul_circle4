#include "Replace.hpp"

int main(int ac, char **av)
{
	if (ac < 4)
	{
		std::cout << "argument error: <filename> <string1> <string2> needed" << std::endl;
		return 1;
	}

	std::string filename = std::string(av[1]);
	std::string str1 = std::string(av[2]);
	std::string str2 = std::string(av[3]);

	Replace replace = Replace(filename, str1, str2);
	replace.openInFile();
	replace.makeLine();
	replace.replaceStr();
	replace.makeOutFile();
	return 0;
}