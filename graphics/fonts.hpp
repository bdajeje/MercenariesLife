#ifndef GRAPHICS_FONTS_HPP
#define GRAPHICS_FONTS_HPP

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

namespace graphics {

class Fonts final
{
  public:

    enum class Type {
      UI, Conversation
    };

    /*!
     * \brief Resource singleton initializer
     * \param directory_path - where to find resources
     */
    static void init(const std::string& directory_path);

    /*!
     * \brief Get a resource
     * \param name of the resource to get
     * \return a pointer to the wanted resource or nullptr
     * \note loads the resource in memory if not already done
     */
    static const sf::Font* get(const std::string& name);
    static const sf::Font* get(Type type);

  protected:

    /*!
     * \brief Resource constructor
     * \param directory_path - where to find resources
     */
    Fonts(const std::string& directory_path);

    /*! Loads a resource */
    void load(const std::string& name);

  private:

    /*! Where to find resources */
    std::string m_directory_path;

    /*! Resources */
    std::map<std::string, sf::Font> m_resources;

    /*! Singleton */
    static std::unique_ptr<Fonts> s_instance;

    /*! Map font type to font name */
    const static std::map<Type, std::string> s_type_to_font;
};

}

#endif // GRAPHICS_FONTS_HPP
