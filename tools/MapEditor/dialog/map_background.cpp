#include "map_background.hpp"

#include <QFileDialog>
#include <QVBoxLayout>

namespace dialog {

MapBackground::MapBackground(QWidget *parent)
  : Dialog(parent)
{
  auto* layout = new QVBoxLayout(this);

  _selected_map_file = new QLabel;
  _select_map_button = new QPushButton("Select a map background image");

  layout->addWidget(_selected_map_file);
  layout->addWidget(_select_map_button);

  connect(_select_map_button, SIGNAL(pressed()), this, SLOT(chooseMap()));

  _select_map_button->setFocus();
}

void MapBackground::chooseMap()
{
  _selected_map_file->setText( QFileDialog::getOpenFileName(this, "Choose a map background file", QString(), "Images (*.png)") );
  emit mapChanged( _selected_map_file->text() );
  close();
}

}
