#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <QWidget>

namespace dialog {

class Dialog : public QWidget
{
  Q_OBJECT

  public:

    explicit Dialog(QWidget *parent = 0);
    virtual ~Dialog() = default;

  protected:

    void keyPressEvent( QKeyEvent* event );

  signals:

  public slots:
};

}

#endif // DIALOG_HPP
