#ifndef RATIONAL_NUMBER_JJ_H
#define RATIONAL_NUMBER_JJ_H

#include <gmp.h>

#ifdef RN

struct RationalNumber
{
  RationalNumber(double a);
  RationalNumber(int a);
  RationalNumber(mpq_t a);
  RationalNumber(const RationalNumber &a);
  RationalNumber();
  ~RationalNumber();

  RationalNumber operator+(const RationalNumber &a) const;
  RationalNumber operator-(const RationalNumber &a) const;
  RationalNumber operator*(const RationalNumber &a) const;
  RationalNumber operator/(const RationalNumber &a) const;
  void operator=(const RationalNumber &a);
  bool operator==(const RationalNumber &a) const;
  bool operator!=(const RationalNumber &a) const;
  bool operator<(const RationalNumber &a) const;
  bool operator>(const RationalNumber &a) const;
  bool operator<=(const RationalNumber &a) const;
  bool operator>=(const RationalNumber &a) const;
  
  double get_value() const;
  
  mpq_t p;
};

#else

struct RationalNumber
{
  RationalNumber(double a);
  RationalNumber(int a);
  RationalNumber(mpf_t a);
  RationalNumber(const RationalNumber &a);
  RationalNumber();
  ~RationalNumber();

  RationalNumber operator+(const RationalNumber &a) const;
  RationalNumber operator-(const RationalNumber &a) const;
  RationalNumber operator*(const RationalNumber &a) const;
  RationalNumber operator/(const RationalNumber &a) const;
  void operator=(const RationalNumber &a);
  bool operator==(const RationalNumber &a) const;
  bool operator!=(const RationalNumber &a) const;
  bool operator<(const RationalNumber &a) const;
  bool operator>(const RationalNumber &a) const;
  bool operator<=(const RationalNumber &a) const;
  bool operator>=(const RationalNumber &a) const;
  
  double get_value() const;
  
  mpf_t p;
};

#endif

#endif // RATIONAL_NUMBER_JJ_H
