#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <map>

#include <QMainWindow>

#include "map_area.hpp"
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
    dialog::MapBackground* _map_background {nullptr};

    /*! Mapping shortut id to shortcut */
    std::map<Shortcut, QKeySequence> _shortcuts;
};

#endif // MAIN_WINDOW_HPP
