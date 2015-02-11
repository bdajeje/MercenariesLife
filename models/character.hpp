#ifndef MODELS_CHARACTER_HPP
#define MODELS_CHARACTER_HPP

#include <string>

namespace models {

class Character
{
  public:

    /*!
     * \brief Character constructor from a file informatioon
     * \param info_filepath - file where to find character informations
     */
    Character(const std::string& info_filepath);

  protected:

    /*! Name */
    std::string m_name;
};

}

#endif // MODELS_CHARACTER_HPP