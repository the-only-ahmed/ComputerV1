#include "Polyv1.hpp"

Poly::Poly() : a(0), b(0), c(0), degree(1) {}
Poly::~Poly() {}

std::string Poly::reduce(std::vector<double> known, std::vector<int> unknown)
{
	std::vector<double> somme;
	degree = *(std::max_element(unknown.begin(), unknown.end()));//unknown.Max();

	for (int i = 0; i <= degree; i++)
		somme.push_back(0);

	for (unsigned int i = 0; i < somme.size(); i++)
	{
		int j = 0;
		for (auto& x : known)
		{
			if (unknown[j] == i)
				somme[i] += x;
			j++;
		}
	}

	std::string res = "";
	int k = 0;
	for (auto& x : somme)
	{
		if (x == 0)
		{
			k++;
			continue;
		}
		switch (k)
		{
		case 0:
			a = x;
			break;
		case 1:
			b = x;
			break;
		case 2:
			c = x;
			break;
		}

		std::ostringstream ss;
		ss << x;
		std::string part(ss.str());
		if (k > 1)
			part += "*x^" + std::to_string(k);
		else if (k == 1)
			part += "*x";
		if (k > 0)
		{
			if (x >= 0)
				part = "+" + part;
		}
		res += part;
		degree = k;
		k++;
	}
	return res;
}

std::string Poly::negative(std::string eq)
{
	std::vector<std::string> str;
	std::string part;
	std::istringstream buf(eq);
	while (std::getline(buf, part, '-'))
		str.push_back(part);

	std::string result = "";
	int length = str.size();
	if (length == 1)
		return eq;
	int i = 0;
	for (auto& s : str)
	{
		result += s;
		if (i < length - 1)
			result += "+ -";
		i++;
	}
	return result;
}

std::string Poly::Handle(std::string eq, int sign) {

	std::vector<double> known;
	std::vector<int> unknown;
	std::vector<std::string> str;
	std::string part;

	eq = this->negative(eq);
	eq.erase(std::remove_if(eq.begin(), eq.end(), ::isspace), eq.end());

	std::istringstream buf(eq);
	while (std::getline(buf, part, '+'))
		str.push_back(part);

	for (auto& s : str)
	{
		if (s == "")
			continue;
		std::vector<std::string> ss;
		std::istringstream buf(s);
		while (std::getline(buf, part, '*'))
			ss.push_back(part);

		int size = ss.size();
		if (size == 2)
		{
			known.push_back(atof(ss[0].c_str()) * sign);
			if (ss[1].find('^') != std::string::npos)
			{
				std::istringstream buf(ss[1]);
				std::vector<std::string> ll;
				while (std::getline(buf, part, '^'))
					ll.push_back(part);
				unknown.push_back(atoi(ll[1].c_str()));
			}
			else
				unknown.push_back(1);
		}
		else if (size == 1)
		{
			if (s.find('x') != std::string::npos || s.find('X') != std::string::npos)
			{
				known.push_back(1 * sign);
				std::istringstream buf(s);
				std::vector<std::string> ll;
				while (std::getline(buf, part, '^'))
					ll.push_back(part);
				unknown.push_back(atoi(ll[1].c_str()));
			}
			else
			{
				known.push_back(atof(s.c_str()) * sign);
				unknown.push_back(0);
			}
		}
	}

	return reduce(known, unknown);
}

std::string Poly::Reduced(std::vector<std::string> str) {

	std::string left = this->Handle(str[0], 1);
	std::string right = this->Handle(str[1], -1);

	return Handle(left + " + " + right, 1);
}

std::string Poly::Result() {

	std::string result = "";
	double x;
	if (degree == 0)
		result = "R";
	else if (degree == 1)
	{
		x = -(a / b);

		std::ostringstream ss;
		ss << x;
		std::string xx(ss.str());

		result = "x = " + xx;
	}
	else if (degree == 2)
	{
		double delta = (b*b) - (4 * a * c);
		if (delta > 0)
		{
			result = "there is two solutions for the equation :\n";
			double x1 = (-b - std::sqrt(delta)) / (2 * c);
			double x2 = (-b + std::sqrt(delta)) / (2 * c);

			std::ostringstream ss;
			ss << x1;
			std::string xx1(ss.str());
			std::ostringstream ssl;
			ssl << x2;
			std::string xx2(ssl.str());

			result += "x1 = " + xx1 + "\nx2 = " + xx2;
		}
		else if (delta == 0)
		{
			double xx = -a / (2 * b);
			std::ostringstream ss;
			ss << xx;
			std::string xxx(ss.str());
			result = "x = " + xxx;
		}
		else
			result = "No Real results for this equation";
	}
	else
		result = "The polynomial degree is stricly greater than 2, I can't solve.";
	return result;
}
