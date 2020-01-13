#ifndef HASH_KEY_JJ_H
#define HASH_KEY_JJ_H

#include <unordered_map>

template <class T>
inline void hash_combine(std::size_t &seed, const T &v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T, size_t d>
std::size_t HashFunc(const T &key)
{
  size_t value = 0;
  for (size_t i = 0; i < d; ++i)
    hash_combine(value, key[i]);

  return value;
}

template<typename T, size_t d>
std::size_t UnorderedHashFunc(const T &key)
{
  T k = key;
  std::sort(k.begin(), k.end());
  
  size_t value = 0;
  for (size_t i = 0; i < d; ++i)
    hash_combine(value, k[i]);
  return value;
}


template<typename T, size_t d>
bool EqualKey(const T &lhs, const T &rhs)
{
  for (size_t i = 0; i < d; ++i)
  {
    if (lhs[i] != rhs[i])
      return false;
  }

  return true;
}

template<typename T, size_t d>
bool UnorderedEqualKey(const T &lhs, const T &rhs)
{
  T lower = lhs;
  T upper = rhs;
  std::sort(lower.begin(), lower.end());
  std::sort(upper.begin(), upper.end());
  
  for (size_t i = 0; i < d; ++i)
  {
    if (lower[i] != upper[i])
      return false;
  }

  return true;
}


#endif // HASH_KEY_JJ_H
