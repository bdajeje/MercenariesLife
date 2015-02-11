#ifndef GRAPHICS_TILE_HPP
#define GRAPHICS_TILE_HPP

#include <memory>
#include <vector>

#include "graphics/drawables/drawable.hpp"

namespace graphics {

class Tile : public Drawable
{
  public:

    /*! Types of tile */
//    enum Type
//    {
//      Grass, Water, Sand
//    };

    /*! \brief Drawing a tile means drawing all objects stacked on the tile in order
     *  \param target - target to draw to
     */
    virtual void draw(sf::RenderTarget& target);

    /*!
     * \brief Add object to draw
     * \param object   - to add onto the drawable stack
     * \param position - (optional) place the object at a specific position into the drawable stack of objects
     *                   if no value is provided, object is added on the top of the stack
     */
    void addObject(std::shared_ptr<Drawable>& object, size_t position = std::numeric_limits<size_t>::max());

  private:

    /*! Object stacked on this tile */
    std::vector<std::shared_ptr<Drawable>> m_objets;
};

}

#endif // GRAPHICS_TILE_HPP
