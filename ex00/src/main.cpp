#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "error only one argument required" << std::endl;
		return (1);
	}
	BitcoinExchange *a;
	a = new BitcoinExchange();

	a->printValue(av[1]);
}