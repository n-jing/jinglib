#include "rational_number.h"

#ifndef RATIONAL_VEC_JJ_H
#define RATIONAL_VEC_JJ_H

#include <array>

struct RationalVec
{
  RationalVec(const double *const p);
  RationalVec(double a, double b, double c);
  RationalVec(const RationalNumber &a,
              const RationalNumber &b,
              const RationalNumber &c);
  RationalVec();
  // RationalVec(const RationalVec& p);
  
  RationalVec operator+(const RationalVec &a) const;
  RationalVec operator-(const RationalVec &a) const;
  RationalNumber operator*(const RationalVec &a) const;
  RationalVec operator*(const RationalNumber &a) const;
  RationalVec operator^(const RationalVec &a) const;

  void operator=(const RationalVec &a);
  bool operator==(const RationalVec &a) const;
  bool operator!=(const RationalVec &a) const;

  std::array<double, 3> get_value() const;
  std::array<RationalNumber, 3> vec;
};

RationalNumber a_dot_the_minus_b_c(const RationalVec &a, const RationalVec &b, const RationalVec &c);


#endif // RATIONAL_VEC_JJ_H
