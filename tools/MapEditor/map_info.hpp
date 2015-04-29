#ifndef MAPINFO_HPP
#define MAPINFO_HPP

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QPoint>

#include "utils/rapidjson/document.h"

class MapInfo final : public QWidget
{
  Q_OBJECT

  public:

    explicit MapInfo(QWidget *parent = 0);

    QString name() const { return _map_name_input->text(); }
    QPoint startPos() const { return QPoint{_start_pos_x_input->value(),_start_pos_y_input->value() }; }
    QPoint nbrTiles() const { return QPoint{_nbr_tiles_w_input->value(),_nbr_tiles_h_input->value() }; }

    /*! Update UI map information */
    void openMap(const rapidjson::Value& document );

  signals:

  public slots:

  private:

    QLineEdit* _map_name_input;
    QSpinBox* _start_pos_x_input;
    QSpinBox* _start_pos_y_input;
    QSpinBox* _nbr_tiles_w_input;
    QSpinBox* _nbr_tiles_h_input;
};

#endif // MAPINFO_HPP
