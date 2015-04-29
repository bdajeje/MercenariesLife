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

void MapArea::openMap(const rapidjson::Value& document, const QString& map_background_path)
{
  // Remove previous tiles
  _tile_infos.clear();

  // Read map size
  auto size_x = document["size"]["w"].GetInt();
  auto size_y = document["size"]["h"].GetInt();

  // Create tiles
  _tile_infos.resize(size_y);
  for( auto& line : _tile_infos )
    line.reserve(size_x);

  // Reaad tiles info
  const auto& tiles = document["tiles"];
  for(rapidjson::SizeType offset = 0; offset < tiles.Size(); ++offset)
  {
    auto x = offset % size_x;
    auto y = offset / size_x;
    _tile_infos[y].emplace_back( new TileInfo );
    _tile_infos[y][x]->setBlocking( tiles[offset]["blocking"].GetBool() );
  }

  // Display new background image
  updateBackgroundImage(map_background_path);
}
