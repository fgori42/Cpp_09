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
	void fullMap(std::map<std::string, float> *map, std::ifstream &in, char del);
	bool validKey(std::string key);
	bool finalCheck(std::string year, std::string month, std::string day);

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &org);
	~BitcoinExchange();
	BitcoinExchange &operator=(const BitcoinExchange &org);

	class NotValidInt : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

	class NotValidIntMax : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

	class TooEarly : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

	class NotValidDate : public std::exception
	{
		private:
			std::string _error;
		public:
			NotValidDate(const std::string &error) throw();
			virtual ~NotValidDate() throw();
			virtual const char *what() const throw();
	};

	class ImpossibleToOpen: public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
	void printValue(std::string str);
};


#endif