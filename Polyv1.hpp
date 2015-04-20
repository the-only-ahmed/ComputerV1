#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cmath>

class Poly
{
private:
	double a;
	double b;
	double c;

	std::string reduce(std::vector<double> known, std::vector<int> unknown);
	std::string negative(std::string eq);
	std::string Handle(std::string eq, int sign);

public:
	Poly();
	~Poly();

	std::string Reduced(std::vector<std::string> str);
	std::string Result();

	int degree;
};
