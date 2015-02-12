#ifndef UTILS_CONVERSIONS_HPP
#define UTILS_CONVERSIONS_HPP

#include <string>

namespace utils {
namespace conversions {

/*! Convert a string to a boolean
 * \param input - to convert
 * \returns true if input equals '1' or 'true', false otherwise
 * \note The decision has been made to note trime the string, so '1 ' will return false
 */
bool boolean(const std::string& input);

}
}

#endif // UTILS_CONVERSIONS_HPP
