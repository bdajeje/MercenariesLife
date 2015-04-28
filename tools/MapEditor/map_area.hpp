#ifndef MAPAREA_HPP
#define MAPAREA_HPP

#include <QWidget>

class MapArea final : public QWidget
{
  Q_OBJECT

  public:

    explicit MapArea(QWidget *parent = 0);
    ~MapArea();

  private:

    void paintEvent(QPaintEvent * /* event */);
    void displayGrid(QPainter& painter) const;

  signals:

  public slots:

    void updateBackgroundImage(QString);
    void toggleGridVisibility();

  private:

    QImage* _background_img {nullptr};

    bool _grid_shown {true};

    static const int _tile_size {75};
};

#endif // MAPAREA_HPP
