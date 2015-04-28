#include "dialog.hpp"

#include <QKeyEvent>

namespace dialog {

Dialog::Dialog(QWidget *parent)
  : QWidget(parent)
{

}

void Dialog::keyPressEvent( QKeyEvent* event )
{
  switch ( event->key() )
  {
    case Qt::Key_Escape:
      close();
      break;
  }
}

}
