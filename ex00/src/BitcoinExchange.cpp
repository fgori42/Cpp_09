#include "BitcoinExchange.hpp"

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &org): _data(org._data)
{
}

bool BitcoinExchange::finalCheck(std::string year, std::string month, std::string day)
{
	std::stringstream ss;
	int intYear, intMonth, intDay;
	ss << year;
	ss >> intYear;
	ss.clear();
	ss << month;
	ss >> intMonth;
	ss.clear();
	ss << day;
	ss >> intDay;
	switch (intMonth)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (intDay> 0 && intDay < 32)
			return true;
		else
			return false;
	case 4:
	case 6:
	case 9:
	case 11:
		if (intDay> 0 && intDay < 31)
			return true;
		else
			return false;
	case 2:
		if (intYear % 4 == 0 && (intYear % 100 != 0 || intYear %400 == 0))
			if (intDay> 0 && intDay < 30)
				return true;
			else
				return false;
		else if (intDay > 0 && intDay <= 28)
			return true;
		else
			return false;
	default:
		return false;
	}
}

bool BitcoinExchange::validKey(std::string key)
{
	int i = 0;
	int j = 0;
	std::string year;
	std::string month;
	std::string day;
	for (int x = 0; key[x]; x++)
		if (!std::isdigit(key[x]) && key[x] != '-')
			return false;
	while (key[j] != '-')
		j++;
	year = key.substr(i, j);
	i = j + 1;
	j++;
	while (key[j] != '-')
		j++;
	month = key.substr(i, j - i);
	i = j + 1;
	day = key.substr(i, key.length() - i);
	//}
	if (year.length() != 4 || month.length() != 2 || day.length() != 2)
		return false;
	return finalCheck(year, month, day);

}

void BitcoinExchange::fullMap(std::map<std::string, float> *map, std::ifstream &in, char del)
{
	std::string line;
	while(getline(in, line))
	{
		int i = line.find(del);
		std::string key = line.substr(0, i);
		std::string value = line.substr(line.find(del) + 1, line.length());
		std::stringstream ss(value);
		float val;
		if (ss >> val)
		{
			(*map)[key] = val;
		}
	}
}

BitcoinExchange::BitcoinExchange()
{
	std::ifstream ab;

	ab.open("data.csv");
	if (ab.fail())
	{
		throw ImpossibleToOpen();
	}
	fullMap(&_data, ab, ',');
	ab.close();
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &org)
{
	if (this != &org)
	{
		_data = org._data;
	}
	return (*this);
}

const char *BitcoinExchange::NotValidInt::what()const throw()
{
	return "Error : not a positive number";
}

const char *BitcoinExchange::NotValidIntMax::what()const throw()
{
	return "Error : too large a nuber";
}

const char *BitcoinExchange::TooEarly::what()const throw()
{
	return "Error : bitcoin didn't exist at this time";
}

BitcoinExchange::NotValidDate::NotValidDate(const std::string &message) throw(): _error("Error : bad imput => " + message) 
{}

const char *BitcoinExchange::NotValidDate::what()const throw()
{
	return _error.c_str();
}

BitcoinExchange::NotValidDate::~NotValidDate() throw()
{}

const char *BitcoinExchange::ImpossibleToOpen::what()const throw()
{
	return "Impossible to open file";
}



void BitcoinExchange::printValue(std::string str)
{
	std::ifstream		in;
	std::string			line;
	std::stringstream	ss;
	size_t				lim;
	int					i;

	in.open(str.c_str());
	if (in.fail())
	{
		throw ImpossibleToOpen();
	}
	while (getline(in, line))
	{
		ss.clear();
		ss.str("");
		try
		{
			if (line == "date | value")
				continue;
			lim = line.find('|');
			if (lim == std::string::npos)
				throw NotValidDate(line);
			std::string key = line.substr(0, lim);
			i = key.length() -1;
			key = key.substr(0, i);
			std::string value = line.substr( lim, line.length() );
			i = 0;
			while(value[i] == ' ' || value[i] == '|')
				i++;
			value = value.substr(i, value.length() - i);
			long long val;
			for (int n = 0; value[n]; n++)
				if (!isdigit(value[n]) && value[n] != '.' && value[n] != '-')
					throw NotValidDate(line);
			ss << value;
			ss >> val;
			if (ss.fail())
				throw NotValidIntMax();
			if (val < 0)
				throw NotValidInt();
			if (val > 1000)
				throw NotValidIntMax();
			for (int x = 0; key[x]; x++)
				if (!std::isdigit(key[x]) && key[x] != '-')
					throw NotValidDate(line);
			if (!validKey(key))
				throw NotValidDate(line);
			std::map<std::string, float>::iterator it = _data.begin();
			it++;
			if (key < it->first)
				throw TooEarly();
			else
			{
				while(key > it->first)
					it++;
				if(key < it->first)
					it--;
				std::cout << key << " => " << val << " = " << val * it->second << std::endl;
			}
		}
		catch(std::exception &err)
		{
			std::cerr << err.what() << std::endl;
		}
	}
}