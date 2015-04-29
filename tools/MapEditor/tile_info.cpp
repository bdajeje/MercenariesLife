#include "tile_info.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>

TileInfo::TileInfo(QWidget *parent)
  : QWidget(parent)
{
  auto* main_layout = new QVBoxLayout(this);

  // Tile position
  auto* position_layout = new QHBoxLayout;
  _position = new QLabel(this);
  position_layout->addWidget(new QLabel("Position"));
  position_layout->addWidget(_position);

  // Tile blocking
  auto* blocking_layout = new QHBoxLayout;
  _blocking = new QCheckBox(this);
  blocking_layout->addWidget(new QLabel("Blocking"));
  blocking_layout->addWidget(_blocking);

  main_layout->addLayout(position_layout);
  main_layout->addLayout(blocking_layout);

  updatePosInfo(0, 0);
}

void TileInfo::updatePosInfo(int x, int y)
{
  _position->setText((std::to_string(x) + "/" + std::to_string(y)).c_str());
}

void TileInfo::setBlocking(bool value)
{
  _blocking->setChecked(value);
}

void TileInfo::resetInfo()
{
  updatePosInfo(-1, -1);
  setBlocking(false);
}
