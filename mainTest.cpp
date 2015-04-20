#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>

bool	premier(int x) {

	for (int i = 2; i <= (x/2); i++)
	{
		if ((x % i) == 0)
			return false;
	}

	return true;
}

int		main(int ac, char** av) {

	if (ac < 2)
		return -1;

	int n = atoi(av[1]);
	std::vector<int> mult;
	std::vector<int> in;
	std::vector<int> out;
	std::vector<std::pair<int, int>> occ;

	while (n > 1)
	{
		for (int i = 2; i <= n ; i++)
		{
			if (!premier(i))
				continue;
			if ((n % i) == 0)
			{
				n /= i;
				mult.push_back(i);
			}
		}
	}

	for (auto& x : mult)
		occ.push_back(std::make_pair(x, std::count(mult.begin(), mult.end(), x)));

	std::sort( occ.begin(), occ.end() );
	occ.erase( unique( occ.begin(), occ.end() ), occ.end() );

	for (auto& x : occ)
	{
		while (x.second > 1)
		{
			x.second -= 2;
			out.push_back(x.first);
		}
		if (x.second == 1)
			in.push_back(x.first);
	}

	int x = 1;
	int d = 1;
	for (auto& a : out)
		x *= a;
	for (auto& a : in)
		d *= a;

	std::cout << x << "V(" << d << ")" << std::endl;

	return 0;
}
