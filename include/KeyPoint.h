#pragma once
namespace wip
{
class KeyPoint
{
public:
  KeyPoint(float x, float y) : x_(x), y_(y) {}

  float x() { return x_; }
  float y() { return y_; }

private:
  float x_, y_;
};

} // namespace wip