
#include <iostream>
#include "Computor.hpp"

int		main(int argc, char **argv)
{
	Computor			computor;
	int				i = 1;
	bool				arg = false;
	bool				debug = false;

	if (argc < 2)
	{
		std::cout << "Usage : ./" << argv[0] << " [-D] [-F] <equation>" << std::endl;
		return (0);
	}
	if (std::string(argv[1]) == "-D")
	{
		i++;
		debug = true;
	}
	if (std::string(argv[1]) == "-F" || (debug && std::string(argv[2]) == "-F"))
	{
		i++;
		arg = true;
	}
	for (; i < argc; i++)
	{
		try
		{
			computor.treatEquation(argv[i], arg, debug);
		}
		catch (std::exception & e)
		{
			std::cout << "Error on equation number " << i << " : " << e.what() << std::endl;
		}
	}
	return (0);
}
