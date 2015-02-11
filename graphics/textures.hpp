#ifndef GRAPHICS_TEXTURES_HPP
#define GRAPHICS_TEXTURES_HPP

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

namespace graphics {

class Textures final
{
  public:

    static const std::map<unsigned int, std::string> IdToName;

  public:

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
    static const sf::Texture* get(const std::string& name);

    /*! Same as get(const std::string& name) but with an ID */
    static const sf::Texture* get(unsigned int id);

  protected:

    /*!
     * \brief Resource constructor
     * \param directory_path - where to find resources
     */
    Textures(const std::string& directory_path);

    /*! Loads a resource */
    void load(const std::string& name);

  private:

    /*! Where to find resources */
    std::string m_directory_path;

    /*! Resources */
    std::map<std::string, sf::Texture> m_resources;

    /*! Singleton */
    static std::unique_ptr<Textures> s_instance;
};

}

#endif // GRAPHICS_TEXTURES_HPP
