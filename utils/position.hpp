#ifndef UTILS_POSITION_HPP
#define UTILS_POSITION_HPP

namespace utils {

struct Position
{
  Position() = default;

  Position(int x, int y)
    : x{x}
    , y{y}
  {}

  int x {0};
  int y {0};
};

}

#endif // UTILS_POSITION_HPP
