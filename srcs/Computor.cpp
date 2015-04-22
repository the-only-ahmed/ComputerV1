#include "Computor.hpp"

// ** PRIVATE ** //

void			Computor::_initComputor( void )
{
	this->_str.clear();
	this->_left.clear();
	this->_right.clear();
	this->_coeffs.clear();
	this->_maxDegree = 0;
	this->_a = 0;
	this->_b = 0;
	this->_c = 0;
}

void			Computor::_checkOthers(std::string str) {

	std::string	s("0123456789*+-^=xX.");// = str.c_str();
	std::string::iterator			it;
	std::string::iterator			ite = str.end();

	for (it = str.begin(); it != ite; it++)
	{
		if (s.find(*it) == std::string::npos)
			throw ComputorException(std::string("Char not allowed : ") + *it);
	}
}

void			Computor::_replaceSubstract( void )
{
	std::string::iterator		begin = this->_str.begin();
	std::string::iterator		back;
	bool								remove;
	size_t							pos = 0;

	while (pos < this->_str.length() && ((pos = this->_str.find('-', pos)) != std::string::npos))
	{
		remove = true ;
		// back = begin + pos;
		// while (back != begin && (*back == '+' || isspace(*back)))
		if (pos == 0)
				remove = false;
		else
		{
				back = begin + pos;
				back--;
				if (*back == '+' || *back == '^' || *back == '=')
					remove = false ;
		}
		if (remove)
		{
			this->_str.replace(pos, 1, "+-");
			pos++;
		}
		pos++;
	}
}

void			Computor::_getLeftRight( void )
{
	size_t		pos;

	pos = this->_str.find('=');
	if (pos == std::string::npos)
		throw ComputorException("Parsing error : no '=' in equation");
	else if (pos == 0)
		throw ComputorException("Parsing error : '=' at start of equation");
	else if ((pos + 1) == this->_str.length())
		throw ComputorException("Parsing error : '=' at end of equation");
	this->_left = this->_str.substr(0, pos);
	this->_right = this->_str.substr(pos + 1);
	if ((this->_str.find('=', ++pos)) != std::string::npos)
		throw ComputorException("Parsing error : multiple '=' present in equation");
}

void 			Computor::_checkToken(std::string token)
{
	int		xes = 0;

	if (xes += std::count(token.begin(), token.end(), 'x') > 1)
		throw ComputorException("Too many 'x'");
	if (xes += std::count(token.begin(), token.end(), 'X') > 1)
		throw ComputorException("Too many 'X'");
	if (std::count(token.begin(), token.end(), '^') > 1)
		throw ComputorException("Too many '^'");
	if (xes > 1)
		throw ComputorException("Too many 'x'");
}

void			Computor::_handle(std::string & part, int sign)
{
	std::istringstream		buffer(part);
	std::string				token;
	Coeff					coeff;
	size_t					pos;
	size_t					pos2;

// 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0
	std::cout << "Full line >>>> " << part << std::endl;
	while (std::getline(buffer, token, '+'))
	{
		std::cout << "token : " << token << std::endl;
		if (token == "")
			continue ;
		coeff.value = 0;
		coeff.degree = 0; //mettre tout le temps a 1 ?
		this->_checkToken(token);
		if ((pos = token.find('*')) != std::string::npos)
		{
			// std::cout << "pos '*': " << pos << std::endl;
			// if (token.substr(0, pos).find("x", 0, pos) != std::string::npos
			// 	|| token.substr(0, pos).find("X", 0, pos) != std::string::npos)
			if (token.substr(0, pos).find('x') != std::string::npos
				|| token.substr(0, pos).find('X') != std::string::npos)
			{
				// std::cout << "stod 1" << std::endl;
				coeff.value = (std::stod(token.substr(pos + 1)) * sign);
				if ((pos2 = token.find("^", 0, pos)) != std::string::npos)
					coeff.degree = std::stod(token.substr(pos2 + 1, pos - 1));
				else
					coeff.degree = 1;
			}
			else
			{
				// std::cout << "stod 2" << std::endl;
				coeff.value = (std::stod(token) * sign); //s arrete bien ?
				if ((pos2 = token.find('^', pos)) != std::string::npos)
					coeff.degree = std::stod(token.substr(pos2 + 1));
				else
					coeff.degree = 1;
			}
		}
		else
		{
			if (token.find('x') != std::string::npos || token.find('X') != std::string::npos)
			{
				// std::cout << "stod" << std::endl;
				coeff.value = 1 * sign;
				if ((pos2 = token.find('^')) != std::string::npos)
					coeff.degree = std::stod(token.substr(pos2 + 1));
				else
					coeff.degree = 1;
				coeff.value = (token.find('-') != std::string::npos)? (coeff.value * -1) : (coeff.value * 1);
			}
			else
			{
				// std::cout << "stod 3" << std::endl;
				coeff.value = (std::stod(token) * sign);
				coeff.degree = 0;
			}
		}
		if (coeff.value != 0)
		{
			if (coeff.degree > this->_maxDegree)
				this->_maxDegree = coeff.degree;
			this->_coeffs.push_back(coeff);
		}
	}
}

void			Computor::_reducedForm( void )
{
	std::list<Coeff>::iterator			it;
	std::list<Coeff>::iterator			it2;
	std::list<Coeff>::iterator			tmp;
	// std::list<Coeff>::iterator			ite;

	for (it = this->_coeffs.begin(); it != this->_coeffs.end(); it++)
	{
		it2 = it;
		it2++;
		while (it2 != this->_coeffs.end())
		{
			tmp = it2;
			tmp++;
			if (it2->degree == it->degree)
			{
				it->value += it2->value;
				this->_coeffs.erase(it2);
			}
			it2 = tmp;
		}
	}
	this->_printCoeffs("Reduced form: ");
}

void			Computor::_printCoeffs( std::string info )
{
	std::list<Coeff>::iterator			it;
	std::list<Coeff>::iterator			ite = this->_coeffs.end();
	size_t									i = 1;

	std::cout << info;
	for (it = this->_coeffs.begin(); it != ite; it++)
	{
		std::cout << it->value << " * X^" << it->degree;
		if (i != this->_coeffs.size())
			std::cout << " + ";
		i++;
	}
	std::cout << " = 0"<< std::endl;
}

void 			Computor::_Alpha(std::string str, double real, double image) {

	std::string alpha;

	if (image == 1)
		alpha = " + i";
	else if (image == -1)
		alpha = " - i";
	else if (image == 0)
		alpha = "";
	else
	{
		if (image < 0)
			alpha = " - " + std::to_string(-image) + " * i";
		else
			alpha = " + " + std::to_string(image) + " * i";
	}

	std::cout << "Number " << str << " : " << real << alpha << std::endl;
}

void			Computor::_findSolutions(bool arg)
{
	if (this->_maxDegree > 2)
	{
		std::cout
			<< "The polynomial degree(" << this->_maxDegree << ") is stricly greater than 2, I can't solve."
			<< std::endl;
		return ;
	}
	this->_findABC();
	if (this->_maxDegree == 0)
		std::cout << "R" << std::endl;
	else if (this->_maxDegree == 1)
	{
		double solution = -(this->_c / this->_b);
		if (solution == -0)
			solution = 0;

		if (arg)
			Fraction(this->_maxDegree, this->_b, this->_c, 0);
		else
			std::cout << "The solution is : " << solution << std::endl;
	}
	else if (this->_maxDegree == 2)
	{
		double		delta = (this->_b * this->_b) - (4 * this->_a * this->_c);
		double		sol_1;
		double		sol_2;

		if (arg)
		{
			Fraction(this->_maxDegree, this->_a, this->_b, delta);
			return;
		}

		if (delta > 0)
		{
			std::cout << "Discriminant is strictly positive, the two solutions are :" << std::endl;
			sol_1 = (-(this->_b) - Math::SQRT(delta)) / (2 * this->_a);
			sol_2 = (-(this->_b) + Math::SQRT(delta)) / (2 * this->_a);

			std::cout << "Number one : " << sol_1 << std::endl;
			std::cout << "Number two : " << sol_2 << std::endl;
		}
		else if (delta == 0)
		{
			std::cout << "The solution is : " << std::endl;
			sol_1 = -(this->_b) / (2 * this->_a);

			std::cout << sol_1 << std::endl;
		}
		else
		{
			// std::cout << "No real results for this equation" << std::endl;
			sol_1 = -(this->_b) / (2 * this->_a);
			double sol_i1 = - Math::SQRT(-delta) / (2 * this->_a);

			sol_2 = -(this->_b) / (2 * this->_a);
			double sol_i2 = Math::SQRT(-delta) / (2 * this->_a);

			this->_Alpha("one", sol_1, sol_i1);
			this->_Alpha("two", sol_2, sol_i2);
		}
	}
}

void			Computor::_findABC( void )
{
	std::list<Coeff>::iterator			it;
	std::list<Coeff>::iterator			ite = this->_coeffs.end();

	for (it = this->_coeffs.begin(); it != ite; it++)
	{
		if (it->value == 0)
			continue ;
		if (it->degree == 0)
			this->_c = it->value;
		else if (it->degree == 1)
			this->_b = it->value;
		else if (it->degree == 2)
			this->_a = it->value;
	}
	std::cout << "a = " << this->_a << std::endl
			  << "b = " << this->_b << std::endl
			  << "c = " << this->_c << std::endl;
}

// ** PUBLIC ** //

Computor::Computor( void ) {}

Computor::~Computor( void ) {}

void			Computor::_debugList()
{
	std::cout << "**** DEBUG ****" << std::endl;
	for (std::list<Coeff>::iterator it = this->_coeffs.begin(); it != this->_coeffs.end(); it++)
		std::cout << "[" << it->value << "][" << it->degree << "]" << std::endl;
	std::cout << "***** END *****" << std::endl;
}

void 			Computor::_checkReducedForm( void )
{
	std::list<Coeff>::iterator			it;
	std::list<Coeff>::iterator			next;

	it = this->_coeffs.begin();
	while (it != this->_coeffs.end())
	{
		next = it;
		next++;
		if (it->value == 0)
			this->_coeffs.erase(it);
		it = next;
	}
	this->_maxDegree = 0;
	for (it = this->_coeffs.begin(); it != this->_coeffs.end(); it++)
	{
		if (Math::getComaNb(it->degree) > 0)
			throw ComputorException("Not solvable equation --> x^" + std::to_string(it->degree));
		if (it->degree > this->_maxDegree)
			this->_maxDegree = it->degree;
	}
}


void			Computor::treatEquation( std::string eq, bool arg )
{
	std::cout << "Treating equation : " << eq << std::endl;
	this->_initComputor();
	this->_str = eq;
	this->_str.erase(std::remove_if(this->_str.begin(), this->_str.end(), ::isspace), this->_str.end());
	this->_checkOthers(this->_str);
//	std::cout << "1 : " << this->_str << std::endl;
	this->_replaceSubstract();
//	std::cout << "2 : " << this->_str << std::endl;
	this->_getLeftRight();

	try
	{
		this->_handle(this->_left, 1);
		this->_handle(this->_right, -1);
	}
	catch (std::exception & e)
	{
		std::cout << "Error : " << e.what() << std::endl;
		throw ComputorException("Handle error");
	}
 	this->_debugList(); // debug
	this->_printCoeffs("Before reduced form: ");
	this->_reducedForm();
	this->_checkReducedForm();
	std::cout << "Polynomial degree: " << this->_maxDegree << std::endl;
 	this->_debugList(); // debug
	this->_findSolutions(arg);
	std::cout << "---------------------------------------" << std::endl;
}

// ** EXCEPTIONS ** //

Computor::ComputorException::ComputorException( std::string const & errorMsg ) throw()
	: std::runtime_error(errorMsg)
{

}

const char*					Computor::ComputorException::what() const throw()
{
	std::string ret = "Computor exception : " + std::string(std::runtime_error::what());
	return ret.c_str();
}

Computor::ComputorException::~ComputorException() throw()
{
	return ;
}
