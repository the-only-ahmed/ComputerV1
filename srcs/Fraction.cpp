#include "Fraction.hpp"

Fraction::Fraction(int deg, double a, double b, double c, double delta) {

   if (deg == 1)
      this->_Resolve_1d(b, c);
   else
      this->_Resolve_2d(a, b, c, delta);
}

Fraction::~Fraction() {}

/* ---------------------------------------------------------------------- */
bool	          Fraction::_Premier(int x) {

   for (int i = 2; i <= (x/2); i++)
   {
      if ((x % i) == 0)
         return false;
   }

   return true;
}

std::vector<int>     Fraction::_Mult(long n) {

   std::vector<int> mult;

   while (n > 1)
   {
      for (int i = 2; i <= n ; i++)
      {
         if (!this->_Premier(i))
            continue;
         if ((n % i) == 0)
         {
            n /= i;
            mult.push_back(i);
         }
      }
   }
   return mult;
}

std::pair<int, int>	 Fraction::_FactoriseSqrt(int n) {

   std::vector<int> mult;
   std::vector<int> in;
   std::vector<int> out;
   std::vector<std::pair<int, int>> occ;

   mult = this->_Mult(n);

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

   return (std::make_pair(x, d));
}

double   Fraction::_Pow(double x, int p) {

   double res = 1;
   for (; p > 0; p--)
      res *= x;
   return res;
}

int   Fraction::_getComaNb(double x) {

   int i = 0;
   double diff = x - floor(x);
   while (diff > 0)
   {
      i++;
      x *= 10;
      diff = x - floor(x);
   }
   return i;
}

void  Fraction::_FactNb(long *a, long *b) {

   std::vector<int> mult = this->_Mult(*a);

   for(auto& x : mult)
   {
      if ((*b % x) == 0)
      {
         *a /= x;
         *b /= x;
      }
   }
}

void  Fraction::_Resolve_1d(double x, double y) {

   unsigned long p = this->_getComaNb(x);
   unsigned long q = this->_getComaNb(y);
   std::string alpha = "ahméd";

   if (p > 0)
   {
      p = this->_Pow(10, p);
      x *= p;
   }
   if (q > 0)
   {
      q = this->_Pow(10, q);
      y *= q;
   }

   p = (p > 0)? p : 1;
   q = (q > 0)? q : 1;

   long a = static_cast<long>(x);
   long b = static_cast<long>(y);

   if (p == q)
   {
      if ((b % a) == 0)
         alpha = std::to_string(-(b / a));
      else
      {
         this->_FactNb(&a, &b);
         alpha = std::to_string(-b) + " / " + std::to_string(a);
      }
   }
   else if (q > p)
   {
      q /= p;
      a *= q;
      this->_FactNb(&a, &b);
      alpha = std::to_string(-b) + " / " + std::to_string(a);
   }
   else
   {
      p /= q;
      b *= p;
      this->_FactNb(&a, &b);
      alpha = std::to_string(-b) + " / " + std::to_string(a);
   }

   std::cout << "The solution is : " << alpha << std::endl;

}

void  Fraction::_Resolve_2d(double a, double b, double c, double delta) {
   std::cout << "The solution is : " << -(b / a) <<std::endl;
   (void)c;
   (void)delta;
}
