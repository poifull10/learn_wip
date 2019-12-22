#pragma once

#include <array>

namespace wip
{
template <typename T, size_t N>
class Point
{
public:
  Point() : array_() {}
  Point(const std::initializer_list<T>& init) : array_(init.begin(), init.end())
  {
  }

  T operator[](size_t i) const { return array_[i]; }
  T& operator[](size_t i) { return array_[i]; }

private:
  std::vector<T> array_;
};

// template <typename T, size_t N>
// Point<T, N> operator+(const Point<T, N>& p1, const Point<T, N>& p2)
// {
//   Point<T, N> p;
//   for (size_t i = 0; i < N; i++)
//   {
//     p[i] = p1[i] + p2[i];
//   }
//   return p;
// }

} // namespace wip
