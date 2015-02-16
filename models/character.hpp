#ifndef MODELS_CHARACTER_HPP
#define MODELS_CHARACTER_HPP

#include <string>

namespace models {

class Character
{
  public:

    /*!
     * \brief Character constructor from a file informatioon
     * \param id - if of the character
     */
    Character(const std::string& id);

    /*! ID getter */
    const std::string& getID() const { return m_id; }

  protected:

    /*! Name */
    std::string m_name;

    /*! Unique ID */
    std::string m_id;
};

}

#endif // MODELS_CHARACTER_HPP
