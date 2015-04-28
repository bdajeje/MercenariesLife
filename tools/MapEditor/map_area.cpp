#include "map_area.hpp"

#include <iostream>

#include <QPainter>

MapArea::MapArea(QWidget *parent)
  : QWidget(parent)
{

}

MapArea::~MapArea()
{
  delete _background_img;
}

void MapArea::paintEvent(QPaintEvent * /* event */)
{
  QPainter painter(this);

  // Draw background if any
  if(_background_img)
  {
    QRect rect(0, 0, painter.device()->width(), painter.device()->height());
    painter.drawImage(rect.topLeft(), *_background_img);
  }

  // Draw grid
  if(_grid_shown)
    displayGrid(painter);
}

void MapArea::displayGrid(QPainter& painter) const
{
  if( !_background_img )
    return;

  const auto nbr_tile_x = _background_img->size().width() / _tile_size;
  const auto nbr_tile_y = _background_img->size().height() / _tile_size;

  for(int y = 0; y < nbr_tile_y; ++y)
  {
    for(int x = 0; x < nbr_tile_x; ++x)
      painter.drawRect(x * _tile_size, y * _tile_size, _tile_size, _tile_size);
  }
}

void MapArea::updateBackgroundImage(QString path)
{
  if(_background_img)
    delete _background_img;

  _background_img = new QImage(path);

  repaint();
}

void MapArea::toggleGridVisibility()
{
  _grid_shown = !_grid_shown;
  repaint();
}
