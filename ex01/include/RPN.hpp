#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include <stack>
# include <exception>
# include <stdexcept>

class RPN
{
private:
	std::stack<double>	_stack;
	double makeResult(char sign, double x, double y);
public:
	RPN();
	RPN(const RPN &org);
	RPN &operator=(const RPN &org);

	void checkTheStack(std::string str);
	class InvalidList : public std::exception
	{
	public:
		const char *what() const throw();
	};
	double execute(std::string str);

	class ZeroForDivider : public std::exception
	{
		public:
			const char *what() const throw();
	};

	~RPN();
};


#endif