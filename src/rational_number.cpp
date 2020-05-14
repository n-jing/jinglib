#include "rational_number.h"

#ifdef RN

RationalNumber::RationalNumber(const RationalNumber &a)
{
  mpq_init(p);
  mpq_set(p, a.p);
}

RationalNumber::RationalNumber(double a)
{
  mpq_init(p);
  mpq_set_d(p, a);
}

RationalNumber::RationalNumber(int a)
{
  mpq_init(p);
  mpq_set_d(p, double(a));
}

RationalNumber::RationalNumber(mpq_t a)
{
  mpq_init(p);
  mpq_set(p, a);
}

RationalNumber::RationalNumber()
{
  mpq_init(p);
}

RationalNumber::~RationalNumber()
{
  mpq_clear(p);
}

RationalNumber RationalNumber::operator+(const RationalNumber &a) const
{
  mpq_t re;
  mpq_init(re);
  mpq_add(re, p, a.p);

  RationalNumber rt(re);
  mpq_clear(re);

  return rt;
}

RationalNumber RationalNumber::operator-(const RationalNumber &a) const
{
  mpq_t re;
  mpq_init(re);
  mpq_sub(re, p, a.p);

  RationalNumber rt(re);
  mpq_clear(re);

  return rt;
}

RationalNumber RationalNumber::operator*(const RationalNumber &a) const
{
  mpq_t re;
  mpq_init(re);
  mpq_mul(re, p, a.p);

  RationalNumber rt(re);
  mpq_clear(re);

  return rt;
}

RationalNumber RationalNumber::operator/(const RationalNumber &a) const
{
  mpq_t re;
  mpq_init(re);
  mpq_div(re, p, a.p);

  RationalNumber rt(re);
  mpq_clear(re);

  return rt;
}

void RationalNumber::operator=(const RationalNumber &a)
{
  mpq_set(p, a.p);
}

bool RationalNumber::operator==(const RationalNumber &a) const
{
  return mpq_equal(p, a.p);
}

bool RationalNumber::operator!=(const RationalNumber &a) const
{
  return !bool(mpq_equal(p, a.p));
}

double RationalNumber::get_value() const
{
  return mpq_get_d(p);
}

bool RationalNumber::operator<(const RationalNumber &a) const
{
  int cmp = mpq_cmp(p, a.p);
  return (cmp < 0);
}

bool RationalNumber::operator>(const RationalNumber &a) const
{
  int cmp = mpq_cmp(p, a.p);
  return (cmp > 0);
}

bool RationalNumber::operator<=(const RationalNumber &a) const
{
  int cmp = mpq_cmp(p, a.p);
  return (cmp <= 0);
}

bool RationalNumber::operator>=(const RationalNumber &a) const
{
  int cmp = mpq_cmp(p, a.p);
  return (cmp >= 0);
}

#else

RationalNumber::RationalNumber(const RationalNumber &a)
{
  mpf_init2(p, 256);
  mpf_set(p, a.p);
}

RationalNumber::RationalNumber(double a)
{
  mpf_init2(p, 256);
  mpf_set_d(p, a);
}

RationalNumber::RationalNumber(int a)
{
  mpf_init(p);
  mpf_set_d(p, double(a));
}


RationalNumber::RationalNumber(mpf_t a)
{
  mpf_init2(p, 256);
  mpf_set(p, a);
}

RationalNumber::RationalNumber()
{
  mpf_init2(p, 256);
}

RationalNumber::~RationalNumber()
{
  mpf_clear(p);
}

RationalNumber RationalNumber::operator+(const RationalNumber &a) const
{
  mpf_t re;
  mpf_init2(re, 256);
  mpf_add(re, p, a.p);

  RationalNumber rt(re);
  mpf_clear(re);

  return rt;
}

RationalNumber RationalNumber::operator-(const RationalNumber &a) const
{
  mpf_t re;
  mpf_init2(re, 256);
  mpf_sub(re, p, a.p);

  RationalNumber rt(re);
  mpf_clear(re);

  return rt;
}

RationalNumber RationalNumber::operator*(const RationalNumber &a) const
{
  mpf_t re;
  mpf_init2(re, 256);
  mpf_mul(re, p, a.p);

  RationalNumber rt(re);
  mpf_clear(re);

  return rt;
}

RationalNumber RationalNumber::operator/(const RationalNumber &a) const
{
  mpf_t re;
  mpf_init2(re, 256);
  mpf_div(re, p, a.p);

  RationalNumber rt(re);
  mpf_clear(re);

  return rt;
}

void RationalNumber::operator=(const RationalNumber &a)
{
  mpf_set(p, a.p);
}

bool RationalNumber::operator==(const RationalNumber &a) const
{
  return mpf_equal(p, a.p);
}

bool RationalNumber::operator!=(const RationalNumber &a) const
{
  return !bool(mpf_equal(p, a.p));
}

double RationalNumber::get_value() const
{
  return mpf_get_d(p);
}

bool RationalNumber::operator<(const RationalNumber &a) const
{
  int cmp = mpf_cmp(p, a.p);
  return (cmp < 0);
}

bool RationalNumber::operator>(const RationalNumber &a) const
{
  int cmp = mpf_cmp(p, a.p);
  return (cmp > 0);
}

bool RationalNumber::operator<=(const RationalNumber &a) const
{
  int cmp = mpf_cmp(p, a.p);
  return (cmp <= 0);
}

bool RationalNumber::operator>=(const RationalNumber &a) const
{
  int cmp = mpf_cmp(p, a.p);
  return (cmp >= 0);
}

#endif
