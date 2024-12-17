#include "RPN.hpp"

int main(int ac, char *av[])
{
	if (ac != 2)
	{
		std::cerr << "Error : bad number of arguments" << std::endl;
		return 1;
	}
	RPN *pool = new RPN();
	try
	{
		{std::cout << pool->execute(av[1])<< std::endl;}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	delete (pool);
	return(0);
}