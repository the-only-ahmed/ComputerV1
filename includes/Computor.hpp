#ifndef COMPUTOR_HPP
#define COMPUTOR_HPP

#include <list>
#include <stdexcept>
#include <string>
#include <cctype>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "Fraction.hpp"

struct Coeff
{
	double			value;
	double			degree;
};


class Computor
{
// ** PRIVATE ** //
private:

	std::string			_str;
	std::string			_left;
	std::string			_right;
	std::list<Coeff>	_coeffs;
	int					_maxDegree;
	double				_a;
	double				_b;
	double				_c;
	bool					_debug;

	Computor( const Computor & src );
	Computor &		operator=( const Computor & src );
	void			_initComputor( void );
	void			_replaceSubstract( void );
	void			_getLeftRight( void );
	void			_handle(std::string & part, int sign);
	void			_reducedForm( void );
	void			_printCoeffs( std::string info );
	void			_findSolutions(bool arg);
	void			_findABC( void );
	void			_debugList();
	void 			_Alpha(std::string str, double real, double image);
	void 			_checkOthers(std::string str);
	void 			_checkToken(std::string token);
	void 			_checkReducedForm( void );

// ** PUBLIC ** //

public:
	Computor( void );
	~Computor( void );

	void			treatEquation( std::string eq, bool arg, bool debug );


// ** EXCEPTIONS ** //

	class ComputorException : public std::runtime_error
	{
	private:
		ComputorException const & operator=(ComputorException const &) throw();
		ComputorException() throw();

	public:
		ComputorException(std::string const & errorMsg) throw();
		~ComputorException() throw();
		virtual const char* 		what() const throw();
	};

};

#endif
