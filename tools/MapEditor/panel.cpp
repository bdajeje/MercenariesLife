#include "panel.hpp"

#include <iostream>

#include <QTabWidget>
#include <QVBoxLayout>

Panel::Panel(QWidget *parent)
  : QWidget(parent)
{
  auto* tabs = new QTabWidget(this);
  tabs->setTabPosition(QTabWidget::TabPosition::West);

  tabs->addTab(&_map_info, "Map");
  tabs->addTab(&_tile_info, "Tile");
}

void Panel::openMap(const rapidjson::Value& document)
{
  _map_info.openMap(document);
  _tile_info.resetInfo();
}
