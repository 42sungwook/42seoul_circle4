#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>
# include <functional>
# include <map>
# include <algorithm> // for std::transform
# include <cctype>    // for std::tolower

struct ToLower
{
    char operator()(char c) const
    {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
};

class Harl
{
	private:
		std::map<std::string, void (Harl::*)()> levelFunctions;

		void debug();
		void info();
		void warning();
		void error();

	public:
		Harl();
		~Harl();
		Harl &operator= (const Harl &object);
		void complain(std::string level);
};

#endif
