#include "tile.hpp"

namespace graphics {

void Tile::draw(sf::RenderTarget& target)
{
  for( const auto& object : m_objets )
    target.draw(object);
}

void Tile::addObject(std::shared_ptr<Drawable>& object, size_t position)
{
  // If position is not specified, or badly choosen, choose end of the stack
  if( position < m_objets.size() )
    m_objets.insert(position, object);
  else
    m_objets.push_back(object);
}

}
