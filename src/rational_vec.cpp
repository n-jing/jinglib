#include "rational_vec.h"
#include <iostream>

using namespace std;

// RationalVec::RationalVec(const RationalVec& p)
// {
//   for (size_t i = 0; i < 3; ++i)
//     vec[i] = p.vec[i];
// }


RationalVec::RationalVec(const double *const p)
{
  for (size_t i = 0; i < 3; ++i)
    vec[i] = RationalNumber(p[i]);
}

RationalVec::RationalVec(double a, double b, double c)
{
  double p[3] = {a, b, c};

  for (size_t i = 0; i < 3; ++i)
    vec[i] = RationalNumber(p[i]);
}

RationalVec::RationalVec(const RationalNumber &a,
                         const RationalNumber &b,
                         const RationalNumber &c)
{
  vec[0] = a;
  vec[1] = b;
  vec[2] = c;
}

RationalVec::RationalVec()
{
  for (size_t i = 0; i < 3; ++i)
    vec[i] = RationalNumber(0);
}

RationalVec RationalVec::operator+(const RationalVec &a) const
{
  RationalVec re;
  for (size_t i = 0; i < 3; ++i)
    re.vec[i] = vec[i] + a.vec[i];

  return re;
}

RationalVec RationalVec::operator-(const RationalVec &a) const
{
  RationalVec re;
  for (size_t i = 0; i < 3; ++i)
    re.vec[i] = vec[i] - a.vec[i];

  return re;
}

RationalNumber RationalVec::operator*(const RationalVec &a) const
{
  RationalNumber re(0);
  for (size_t i = 0; i < 3; ++i)
    re = re + (vec[i] * a.vec[i]);
  
  return re;
}

RationalVec RationalVec::operator^(const RationalVec &a) const
{
  RationalVec re;
  for (size_t i = 0; i < 3; ++i)
    re.vec[i] = vec[(i+1)%3] * a.vec[(i+2)%3] - vec[(i+2)%3] * a.vec[(i+1)%3];

  return re;
}

void RationalVec::operator=(const RationalVec &a)
{
  for (size_t i = 0; i < 3; ++i)
    vec[i] = a.vec[i];
}

bool RationalVec::operator==(const RationalVec &a) const
{
  for (size_t i = 0; i < 3; ++i)
  {
    if (vec[i] != a.vec[i])
      return false;
  }

  return true;
}

bool RationalVec::operator!=(const RationalVec &a) const
{
  return !(*this == a);
}

std::array<double, 3> RationalVec::get_value() const
{
  array<double, 3> re;
  for (size_t i = 0; i < 3; ++i)
    re[i] = vec[i].get_value();

  return re;
}

RationalNumber a_dot_the_minus_b_c(const RationalVec &a, const RationalVec &b, const RationalVec &c)
{
  return a * (b - c);
}

RationalVec RationalVec::operator*(const RationalNumber &a) const
{
  RationalVec rv;
  for (size_t i = 0; i < 3; ++i)
  {
    rv.vec[i] = a * vec[i];
  }
  return rv;
}
