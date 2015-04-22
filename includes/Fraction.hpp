#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <vector>
#include <string>

#include "Math.hpp"

class Fraction
{
private:
   bool                  _negative;
   bool                  _D2;

   std::pair<int, int>	 _FactoriseSqrt(int n);
   void                  _Resolve_1d(double a, double b, std::string str);
   void                  _Resolve_2d(double a, double b, double delta);
   std::vector<int>      _Mult(long n);
   void                  _PositivD(double a, double b, std::pair<int, int> racineD, unsigned long p);

   void                  _ahmed(double a, double b, double f, int Rf, int Rd, int Pd, bool ssn);
   void                  _aaa(double *a, double *b);

   template<typename T>
   void                  _FactNb(T *a, T *b);

public:
   Fraction(int degree, double a, double b, double delta);
   ~Fraction();
};

template<typename T>
void  Fraction::_FactNb(T *a, T *b) {

   long pa = static_cast<long>(*a);
   long pb = static_cast<long>(*b);
   std::vector<int> mult = this->_Mult(*a);

   for(auto& x : mult)
   {
      if ((pa % x) == 0 && (pb % x) == 0)
      {
         pa /= x;
         pb /= x;
      }
   }

   *a = pa;
   *b = pb;
}

#endif
