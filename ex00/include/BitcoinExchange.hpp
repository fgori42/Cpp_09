#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include <exception>
# include <stdexcept>
# include <sstream>

class BitcoinExchange
{
private:
	std::map<std::string,float> _data;
	std::map<std::string,float> _src;
	void fullMap(std::map<std::string, float> *map, std::ifstream &in, char del);
	bool validKey(std::string key);

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &org);
	BitcoinExchange(char *infile);
	~BitcoinExchange();
	BitcoinExchange &operator=(const BitcoinExchange &org);

	class NotValidInt : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

	class NotValidDate : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

	class ImpossibleToOpen: public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
	void printValue();
};


#endif