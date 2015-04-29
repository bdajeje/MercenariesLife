#ifndef TILEINFO_HPP
#define TILEINFO_HPP

#include <QLabel>
#include <QWidget>
#include <QCheckBox>

class TileInfo final : public QWidget
{
  Q_OBJECT

  public:

    explicit TileInfo(QWidget *parent = 0);

    void resetInfo();

    void setBlocking(bool value);

  signals:

  public slots:

  private:

    void updatePosInfo(int x, int y);

  private:

    QLabel* _position;
    QCheckBox* _blocking;
};

#endif // TILEINFO_HPP
