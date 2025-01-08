#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		if (ac == 1)
			std::cerr << "Error: could not open file." <<std::endl;
		else
			std::cerr << "error only one argument required" << std::endl;
		return (1);
	}
	BitcoinExchange *a;
	try
	{
		a = new BitcoinExchange();

		a->printValue(av[1]);
		delete(a);
	}
	catch(const std::exception& e)
	{
		delete(a);
		std::cerr << e.what() << '\n';
	}
}