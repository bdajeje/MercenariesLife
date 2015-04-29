#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <map>

#include <QMainWindow>

#include "map_area.hpp"
#include "panel.hpp"
#include "dialog/map_background.hpp"

class MainWindow final : public QMainWindow
{
  Q_OBJECT

  public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:

    enum class Shortcut {NewMap, SaveMap, OpenMap, ToggleGridVisibility, ChooseMapBackgroundImage};

    void createWidgets();
    void createWidgetConnections();
    void createMenuBar();
    void centerModal(QWidget* modal);

  public slots:

    void newMap();
    void saveMap();
    void openMap();
    void showMapBackgroundDialog();

  private:

    MapArea* _map_area;
    Panel* _panel;
    dialog::MapBackground* _map_background {nullptr};

    /*! Mapping shortut id to shortcut */
    std::map<Shortcut, QKeySequence> _shortcuts;

    /*! Directory where to save files are located */
    QString _map_dir;
};

#endif // MAIN_WINDOW_HPP
