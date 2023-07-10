#include "Replace.hpp"

int main(int ac, char **av)
{
	std::string filename;
	std::string str1;
	std::string str2;
	
	if (ac < 4)
	{
		std::cout << "argument error: <filename> <string1> <string2> needed" << std::endl;
		return 1;
	}
	filename = av[1];
	str1 = av[2];
	str2 = av[3];
	Replace replace = Replace(filename, str1, str2);
	replace.openInFile();
	replace.makeLine();
	replace.replaceStr();
	replace.makeOutFile();
	return 0;
}