// ComputerV1.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "Polyv1.hpp"

int main(int argc, char* argv[])
{
	/*for (auto& s : tokens) // foreach (string s in tokens)
	  std::cout << '"' << s << '"' << '\n';*/

	std::cout << "Entrer l'equation : ";
	char s[1000];
	std::string eq;
	std::cin.getline(s, sizeof(s));
	eq = s;
	std::istringstream buf(eq);

	std::string part;
	std::vector<std::string> str;
	Poly pol;

	while (std::getline(buf, part, '='))
		str.push_back(part);

	//std::string str[] = eq.Split('=');

	eq = pol.Reduced(str);
	std::cout << "Reduced form: " << eq << " = 0" << std::endl;
	std::cout << "Polynomial degree: " << pol.degree << std::endl;
	std::cout << pol.Result() << std::endl;
	return 0;
}
