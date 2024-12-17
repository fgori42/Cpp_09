#include "RPN.hpp"

RPN::RPN()
{
}

const char *RPN::InvalidList::what() const throw()
{
	return "invalid argument";
}

const char *RPN::ZeroForDivider::what() const throw()
{
	return "the current divider is 0";
}

void RPN::checkTheStack(std::string str)
{
	int nb = 0;
	int operation = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] != ' ' && (str[i + 1] != ' ' && str[i + 1] != '\0'))
		{
			throw InvalidList();
		}
		if (isdigit(str[i]))
			nb++;
		else if (str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == '-')
			operation++;
	}
	if (nb != operation + 1)
		throw InvalidList();
}

double RPN::makeResult(char sign, double x, double y)
{
	switch (sign)
	{
	case '+':
		return (x + y);

	case '-':
		return (x - y);

	case '*':
		return (x * y);
	
	case '/':
	{
		if (y == 0)
			throw ZeroForDivider();
		return (x / y);
	}
	default:
		return (0);
	}
}

double RPN::execute(std::string str)
{
	double x;
	double y;
	double result;

	checkTheStack(str);
	
	for (int i = 0; str[i]; i++)
	{
		if (isdigit(str[i]))
			_stack.push((double)(str[i] - 48));
		else if (str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == '-')
		{
			if (_stack.size() < 2)
				throw InvalidList();
			else
			{
				y = _stack.top();
				_stack.pop();
				x = _stack.top();
				_stack.pop();
				result = makeResult(str[i], x, y);
				_stack.push(result);
			}
		} 
	}
	return(_stack.top());
}

RPN::RPN(const RPN &org) : _stack(org._stack)
{
}

RPN &RPN::operator=(const RPN &org)
{
	if (this != &org)
		_stack = org._stack;
	return (*this);
}

RPN::~RPN()
{
}
