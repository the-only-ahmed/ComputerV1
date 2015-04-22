#include "Math.hpp"

int      Math::PGCD(int a , int b) {

   if (a == b)
      return a;
   else if (a > b)
      return PGCD(a - b, b);

   return PGCD(a , b - a);
}

bool	   Math::isPrime(int x) {

   for (int i = 2; i <= (x/2); i++)
   {
      if ((x % i) == 0)
         return false;
   }

   return true;
}

double   Math::POW(double x, int p) {

   double res = 1;
   for (; p > 0; p--)
      res *= x;
   return res;
}

int      Math::getComaNb(double x) {

   int i = 0;
   double diff = x - static_cast<int>(x);
   while (diff > 0)
   {
      i++;
      x *= 10;
      diff = x - static_cast<int>(x);
   }
   return i;
}

/* ------------------------------ Square Root ------------------------------ */

double			Math::_powerOfTen(int num)
{
   double 	rst = 1;
   int		i = 0;

   if (num >= 0)
   {
      while (i < num)
      {
         rst *= 10;
         i++;
      }
   }
   else
   {
      while (i < (0 - num))
      {
         rst *= 0.1;
         i++;
      }
   }
   return (rst);
}

double			Math::SQRT(double a)
{
   double 	rst = 0;
   int 	   i = 8;
   double 	j = 1;

   while (i > 0)
   {
      if (a - ((2 * rst ) + (j * Math::_powerOfTen(i)))*(j * Math::_powerOfTen(i)) >= 0)
      {
         while ((a - (( 2 * rst ) + ( j * Math::_powerOfTen(i))) *
            (j * Math::_powerOfTen(i)) >= 0) && (j < 10))
            j++;

         j--;
         a -= (( 2 * rst ) + ( j * Math::_powerOfTen(i)))*( j * Math::_powerOfTen(i));
         rst += j * Math::_powerOfTen(i);
         j = 1.0;

      }
      i--;
   }
   return (Math::_square_suite(rst, j, a));
}

double			Math::_square_suite(double rst, double j, double a)
{
   int		i = 0;

   while (i >= -8)
   {
      if(a - ((2 * rst) + (j * Math::_powerOfTen(i))) * (j * Math::_powerOfTen(i)) >= 0)
      {
         while(a - ((2 * rst) + (j * Math::_powerOfTen(i))) *
            (j * Math::_powerOfTen(i)) >= 0)
            j++;

         j--;
         a -= ((2 * rst) + (j * Math::_powerOfTen(i))) * (j * Math::_powerOfTen(i));
         rst += j * Math::_powerOfTen(i);
         j = 1.0;
      }
      i--;
   }
   return (rst);
}
