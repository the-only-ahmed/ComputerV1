#include "Fraction.hpp"

Fraction::Fraction(int deg, double a, double b, double delta) : _D2(false) {

   if (deg == 1)
      this->_Resolve_1d(a, b, "The solution is :");
   else
      this->_Resolve_2d(a, b, delta);
}

Fraction::~Fraction() {}

/* ---------------------------------------------------------------------- */
std::vector<int>     Fraction::_Mult(long n) {

   std::vector<int> mult;

   n = Math::ABS(n);
   while (n > 1)
   {
      for (int i = 2; i <= n ; i++)
      {
         if (!Math::isPrime(i))
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
   bool neg = false;

   if (n == 0)
      return (std::make_pair(1, 0));
   if (n < 0)
   {
      neg = true;
      n *= -1;
   }

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

   if (neg)
      x *= -1;

   return (std::make_pair(x, d));
}

void  Fraction::_Resolve_1d(double x, double y, std::string str) {

   unsigned long p = Math::getComaNb(x);
   unsigned long q = Math::getComaNb(y);
   std::string alpha = "ahméd";

   if (p > 0)
   {
      p = Math::POW(10, p);
      x *= p;
   }
   if (q > 0)
   {
      q = Math::POW(10, q);
      y *= q;
   }

   p = (p > 0)? p : 1;
   q = (q > 0)? q : 1;

   long a = static_cast<long>(x);
   long b = static_cast<long>(y);

   if (this->_D2)
      b *= -1;
   if (-b < 0 && a < 0)
   {
      a *= -1;
      b *= -1;
   }

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

   std::cout << str << alpha << std::endl;
}

void  Fraction::_Resolve_2d(double a, double b, double delta) {

   unsigned long p = 0;
   if (delta != 0)
   {
      p = Math::getComaNb(delta);
      if (p > 0)
      {
         p = Math::POW(10, p);
         delta *= p;
      }
   }

   std::pair<int, int> racineD = this->_FactoriseSqrt(static_cast<int>(delta));

   if (delta == 0)
      this->_Resolve_1d(2 * a, b, "The solution is :");
   else
   {
      if (delta > 0)
         this->_negative = false;
      else
         this->_negative = true;
      this->_PositivD(a, b, racineD, p);
   }
}

void  Fraction::_PositivD(double a, double b, std::pair<int, int> racineD, unsigned long p) {

   if (this->_negative)
      std::cout << "Discriminant is strictly negative, the two solutions are :" << std::endl;
   else
      std::cout << "Discriminant is strictly positive, the two solutions are :" << std::endl;

   if (p == 0 && racineD.second <= 1)
   {
      this->_D2 = true;
      int x = -b - (racineD.first * racineD.second);
         this->_Resolve_1d(2 * a, x, "Number one : ");
      x = -b + (racineD.first * racineD.second);
         this->_Resolve_1d(2 * a, x, "Number two : ");
      return;
   }
   double f = 1;

   std::pair<int, int> part = this->_FactoriseSqrt(static_cast<int>(p));
   if (p > 0)
   {
      this->_FactNb(&racineD.first, &part.first);
      f = part.first;
   }

   f *= 2 * a;

   std::cout << "Number one : ";
   this->_print(2 * a, b, f, racineD.first, racineD.second, part.second, true);
   std::cout << "Number two : ";
   this->_print(2 * a, b, f, racineD.first, racineD.second, part.second, false);
}

void  Fraction::_coma(double *a, double *b) {

   unsigned int pA = 1;
   if (*a != 0)
   {
      pA = Math::getComaNb(*a);
      if (pA > 0)
      {
         pA = Math::POW(10, pA);
         *a *= pA;
      }
      else
         pA = 1;
   }
   unsigned int pB = 1;
   if (*b != 0)
   {
      pB = Math::getComaNb(*b);
      if (pB > 0)
      {
         pB = Math::POW(10, pB);
         *b *= pB;
      }
      else
         pB = 1;
   }

   (*a) *= pB;
   (*b) *= pA;
   this->_FactNb(a, b);
}

void  Fraction::_print(double a, double b, double f, int Rf, int Rd, int Pd, bool ssn) {

   this->_coma(&a, &b);
   double rf = Rf;
   this->_coma(&f, &rf);
   Rf = static_cast<int>(rf);

   int x = static_cast<int>(a);
   int y = static_cast<int>(b);
   int z = static_cast<int>(f);

   int pgcdUp = Math::PGCD(Math::ABS(y), Math::ABS(Rf));
   int pgcdDown = Math::PGCD(Math::ABS(x), Math::ABS(z));

   int restUp_1 = (-b / pgcdUp);
   int restUp_2 = (Rf / pgcdUp);

   int restDown_1 = a / pgcdDown;
   int restDown_2 = f / pgcdDown;
   int restDown = 0;

   if (restDown_1 == restDown_2)
      restDown = restDown_1;

   if (restDown < 0)
   {
      restDown *= -1;
      restUp_1 *= -1;
      restUp_2 *= -1;
   }
   if (ssn)
      restUp_2 *= -1;
   std::string sign = "+";
   if (restUp_2 < 0)
   {
      restUp_2 *= -1;
      sign = "-";
   }

   this->_FactNb(&pgcdUp, &pgcdDown);

   std::string RU_1 = (restUp_1 == 0)? std::string("") : std::to_string(restUp_1);
   std::string RU_2 = (restUp_2 == 1)? std::string("") : std::to_string(restUp_2);

   if (this->_negative)
      RU_2 += "i";

   bool par = true;

   if ((pgcdUp % pgcdDown) == 0)
   {
      if ((pgcdUp / pgcdDown) != 1)
         std::cout << (pgcdUp / pgcdDown) << " * ";
      else
         par = false;
   }
   else
      std::cout << "( " << pgcdUp << " / " << pgcdDown << " ) * ";

   if (par)
      std::cout << " (( ";

   auto func = [&] () {

      if (Pd > 1)
         std::cout << " (";
      if (Rd > 1)
         std::cout << " V(" << Rd << ") ";
      if (Pd > 1)
         std::cout << " / V(" << Pd << "))";
   };

   if (restDown != 0)
   {
      std::cout << RU_1 << " ";
      if (Rd > 1 || Pd > 1 || RU_2 != "")
      {
         if (!(RU_1 == "" && sign == "+"))
            std::cout << sign;
         std::cout << " " << RU_2;
      }
      func();
      if (restDown > 1)
         std::cout << " ) / "<< restDown << " )";
      else if (par)
         std::cout << " )";
      std::cout << std::endl;
   }
   else
   {
      if ((restUp_1 % restDown_1) == 0)
      {
         if ((restUp_1 / restDown_1) != 0)
            std::cout << (restUp_1 / restDown_1) << sign;
         else if (sign == "-")
            std::cout << sign;
      }
      else
         std::cout << "( " << restUp_1 << " / " << restDown_1 << " ) " << sign;

      std::cout << " ( " << RU_2;
      func();
      std::cout << " ) ";
      if (restDown_2 != 1)
         std::cout << " / " << restDown_2;
      std::cout << std::endl;
   }
}
