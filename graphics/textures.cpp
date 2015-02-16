#include "textures.hpp"

#include <iostream>

#include "utils/files/file.hpp"

namespace graphics {

std::unique_ptr<Textures> Textures::s_instance;

void Textures::init(const std::string& directory_path)
{
  // Initialize only once
  if(s_instance)
    return;

  s_instance.reset( new Textures(directory_path) );
}

Textures::Textures(const std::string& directory_path)
  : m_directory_path{ utils::files::ensureDirEnd(directory_path) }
{}

void Textures::load(const std::string& name)
{
  m_resources[name].loadFromFile( m_directory_path + name );
}

const sf::Texture* Textures::get(const std::string& name)
{
  if(!s_instance)
  {
    std::cerr << "Trying to use an uninitailized textures manager!" << std::endl;
    return nullptr;
  }

  // Try to find already loaded resource
  auto found = s_instance->m_resources.find(name);
  if( found != s_instance->m_resources.end() )
    return &(found->second);

  // Resource isn't in memory, let's load it
  s_instance->load(name);
  return &s_instance->m_resources[name];
}

}
