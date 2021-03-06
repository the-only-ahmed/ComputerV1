
#include <iostream>
#include "Computor.hpp"

int		main(int argc, char **argv)
{
	Computor			computor;
	int                 i;
	bool				arg = false;
	bool				debug = false;

	if (argc < 2)
	{
		std::cout << "Usage : " << argv[0] << " [-D] [-F] <equation>" << std::endl;
		return (0);
	}
	for (i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-D")
			debug = true;
		else if (std::string(argv[i]) == "-F")
			arg = true;
	}
	if (((debug || arg) && argc == 2) || (debug && arg && argc == 3))
		std::cout << "Usage : " << argv[0] << " [-D] [-F] <equation>" << std::endl;
	// if (std::string(argv[1]) == "-D")
	// {
	// 	i++;
	// 	if (argc == 2)
   //          std::cout << "Usage : " << argv[0] << " [-D] [-F] <equation>" << std::endl;
   //      debug = true;
	// }
	// if (std::string(argv[1]) == "-F" || (argc > 2 && debug && std::string(argv[2]) == "-F"))
	// {
	// 	i++;
   //      if ((debug && argc == 3) || argc == 2)
   //          std::cout << "Usage : " << argv[0] << " [-D] [-F] <equation>" << std::endl;
	// 	arg = true;
	// }
	for (i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) != "-F" && std::string(argv[i]) != "-D")
		{
			try
			{
				computor.treatEquation(argv[i], arg, debug);
			}
			catch (std::exception & e)
			{
				std::cout << "Error on equation : '" << argv[i] << "' : " << e.what() << std::endl;
			}
		}
	}
	return (0);
}
