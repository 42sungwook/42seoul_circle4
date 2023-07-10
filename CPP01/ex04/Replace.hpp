#ifndef REPLACE_HPP
# define REPLACE_HPP

# include <iostream>
# include <fstream>

class Replace {
	
	private:
		std::string _filename;
		std::string _str1;
		std::string _str2;
		std::string	_line;
		std::ifstream *_inputFile;

	public:
		Replace(const std::string& filename, const std::string& str1, const std::string& str2);
		~Replace();
		Replace &operator= (const Replace &name);
		Replace(const Replace &object);
		void	openInFile();
		void	replaceStr();
		void	makeLine();
		void	makeOutFile();
};

#endif
