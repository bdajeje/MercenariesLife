#include "map_info.hpp"

#include <iostream>

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

MapInfo::MapInfo(QWidget *parent)
  : QWidget(parent)
{
  auto* main_layout = new QVBoxLayout(this);

  _map_name_input = new QLineEdit(this);
  _start_pos_x_input = new QSpinBox(this);
  _start_pos_y_input = new QSpinBox(this);
  _nbr_tiles_w_input = new QSpinBox(this);
  _nbr_tiles_h_input = new QSpinBox(this);

  auto* start_pos_layout = new QHBoxLayout;
  start_pos_layout->addWidget(_start_pos_x_input);
  start_pos_layout->addWidget(_start_pos_y_input);
  auto* nbr_tiles_layout = new QHBoxLayout;
  nbr_tiles_layout->addWidget(_nbr_tiles_w_input);
  nbr_tiles_layout->addWidget(_nbr_tiles_h_input);

  main_layout->addWidget(new QLabel("Map name"));
  main_layout->addWidget(_map_name_input);
  main_layout->addWidget(new QLabel("Start positions"));
  main_layout->addLayout(start_pos_layout);
  main_layout->addWidget(new QLabel("Number of tiles"));
  main_layout->addLayout(nbr_tiles_layout);
}

void MapInfo::openMap( const rapidjson::Value& document )
{
  _map_name_input->setText( document["name"].GetString() );
  _start_pos_x_input->setValue( document["start_pos"]["x"].GetInt() );
  _start_pos_y_input->setValue( document["start_pos"]["y"].GetInt() );
  _nbr_tiles_w_input->setValue( document["size"]["w"].GetInt() );
  _nbr_tiles_h_input->setValue( document["size"]["h"].GetInt() );
}
