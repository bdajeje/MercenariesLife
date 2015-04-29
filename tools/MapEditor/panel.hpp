#ifndef PANEL_HPP
#define PANEL_HPP

#include <QWidget>

#include "map_info.hpp"
#include "tile_info.hpp"
#include "utils/rapidjson/document.h"

class Panel final : public QWidget
{
  Q_OBJECT

  public:

    explicit Panel(QWidget *parent = 0);

    const MapInfo& mapInfo() const { return _map_info; }

    /*! Update UI map information */
    void openMap(const rapidjson::Value& document);

  signals:

  public slots:

  private:

    MapInfo _map_info;
    TileInfo _tile_info;
};

#endif // PANEL_HPP
