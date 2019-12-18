#pragma once

#include <array>

namespace wip
{
  template<typename T, size_t N>
  class Point
  {
    public:
    Point() : array_() {}

    T& operator[](size_t i)
    {
      return array_.at(i);
    }

    Point operator+ (const Point& point) {
      Point p;
      for (size_t i=0;i<N; i++){
        p[i] = (*this)[i] + point[i];
      }
      return p;
    }
    private:
    std::array<T, N> array_;

  };
}