
#include <iostream>
#include "Computor.hpp"

int		main(int argc, char **argv)
{
	Computor			computor;
	int				i;
	bool				arg = false;

	if (argc < 2)
	{
		std::cout << "Usage : ./" << argv[0] << " [-F] <equation>" << std::endl;
		return (0);
	}
	if (std::string(argv[1]) == "-F")
		arg = true;
	for (i = 1; i < argc; i++)
	{
		try
		{
			computor.treatEquation(argv[i], arg);
		}
		catch (std::exception & e)
		{
			std::cout << "Error on equation number " << i << " : " << e.what() << std::endl;
		}
	}
	return (0);
}
