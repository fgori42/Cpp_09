#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &org): _data(org._data), _src(org._src)
{
}

bool BitcoinExchange::validKey(std::string key)
{
	for (int i = 0; key[i] == 0; i++)
		;
	int j = key.find('-');
	
}

void BitcoinExchange::fullMap(std::map<std::string, float> *map, std::ifstream &in, char del)
{
	std::string line;
	while(getline(in, line))
	{
		int i = line.find(del);
		if (line[i] == '|')
			i--;
		std::string key = line.substr(0, i);
		std::string value = line.substr(line.find(del) + 1, line.length());
		if (!validKey(key))
			throw NotValidDate();
		std::stringstream ss(value);
		float val;
		if (ss >> val)
		{
			if ((val > 0 && val < 1000 )|| del == ',')
				(*map)[key] = val;
			else
				throw NotValidInt();
		}
	}
}

BitcoinExchange::BitcoinExchange(char *infile)
{
	std::ifstream in;
	std::ifstream ab;

	in.open(infile);
	if (in.fail())
	{
		throw ImpossibleToOpen();
	}
	fullMap(&_src, in, '|');
	in.close();
	ab.open("data.csv");
	if (ab.fail())
	{
		throw ImpossibleToOpen();
	}
	fullMap(&_data, ab, ',');
	in.close();
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &org)
{
	if (this != &org)
	{
		_data = org._data;
		_src = org._src;
	}
	return (*this);
}

const char *BitcoinExchange::NotValidInt::what()const throw()
{
	return "int not valid";
}

const char *BitcoinExchange::NotValidDate::what()const throw()
{
	return "not valed date";
}

const char *BitcoinExchange::ImpossibleToOpen::what()const throw()
{
	return "Impossible to open file";
}

void BitcoinExchange::printValue()
{
	for (std::map<std::string, float>::iterator i = _data.begin(); i != _data.end(); i++)
	{
		for (std::map<std::string, float>::iterator j = _src.begin(); j != _src.end(); j++)
			if (i->first == j->first)
				{
					std::cout << "data key-> " << i->first << " data value-> " << i->second << "   src key-> " << j->first << " src value-> " << j->second << std::endl;
				}
			//else
			//	{
			//		std::cout << "______" << i->first << "____" << "   src key____"<< j->first<< "___" << std::endl;
			//	}
	}
}