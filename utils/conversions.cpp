#include "conversions.hpp"

namespace utils {
namespace conversions {

bool boolean(const std::string& input)
{
  return (input == "1" || input == "true");
}

}
}
