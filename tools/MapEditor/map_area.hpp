#ifndef MAPAREA_HPP
#define MAPAREA_HPP

#include <memory>

#include <QWidget>

#include "tile_info.hpp"
#include "utils/rapidjson/document.h"

class MapArea final : public QWidget
{
  Q_OBJECT

  public:

    explicit MapArea(QWidget *parent = 0);
    ~MapArea();

    void openMap(const rapidjson::Value& document, const QString& map_background_path);

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

    /*! Each tile has an associated TileInfo */
    std::vector<std::vector<std::unique_ptr<TileInfo>>> _tile_infos;

    static const int _tile_size {75};
};

#endif // MAPAREA_HPP
