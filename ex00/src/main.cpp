#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "error only one argument required" << std::endl;
		return (1);
	}
	BitcoinExchange *a;
	try{
		a = new BitcoinExchange(av[1]);

		a->printValue();
	}
	catch(std::exception &error)
	{
		std::cerr << error.what() << std::endl;
	}

}