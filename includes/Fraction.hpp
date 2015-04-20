#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <vector>
#include <cmath>

class Fraction
{
private:
   bool	                _Premier(int x);
   std::pair<int, int>	 _FactoriseSqrt(int n);
   double                _Pow(double x, int p);
   int                   _getComaNb(double x);
   void                  _Resolve_1d(double a, double b);
   void                  _Resolve_2d(double a, double b, double c, double delta);
   std::vector<int>      _Mult(long n);
   void                  _FactNb(long *a, long *b);

public:
   Fraction(int degree, double a, double b, double c, double delta);
   ~Fraction();
};

#endif
