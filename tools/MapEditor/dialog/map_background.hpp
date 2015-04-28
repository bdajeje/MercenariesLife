#ifndef MAPBACKGROUND_HPP
#define MAPBACKGROUND_HPP

#include <QLabel>
#include <QPushButton>

#include "dialog/dialog.hpp"

namespace dialog {

class MapBackground : public Dialog
{
  Q_OBJECT

  public:

    explicit MapBackground(QWidget *parent = 0);

  signals:

    void mapChanged(QString);

  public slots:

    void chooseMap();

  private:

    QLabel* _selected_map_file;
    QPushButton* _select_map_button;
};

}

#endif // MAPBACKGROUND_HPP
