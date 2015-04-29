#include "main_window.hpp"

#include <iostream>

#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QHBoxLayout>

#include "utils/rapidjson/document.h"
#include "utils/files.hpp"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  createWidgets();
  createWidgetConnections();
  createMenuBar();
}

void MainWindow::createWidgets()
{
  auto* main_widget = new QWidget();
  auto* main_layout = new QHBoxLayout(main_widget);

  // Panels
  _panel = new Panel(this);
  _panel->setFixedWidth(200);

  // Map area
  _map_area = new MapArea(this);
  _map_area->setMinimumSize( 600, 600 );

  // Add widgets to layout
  main_layout->addWidget(_panel);
  main_layout->addWidget(_map_area);

  // Dialogs
  _map_background = new dialog::MapBackground;

  setCentralWidget(main_widget);
}

MainWindow::~MainWindow()
{
  delete _map_background;
}

void MainWindow::createWidgetConnections()
{
  connect( _map_background, SIGNAL(mapChanged(QString)), _map_area, SLOT(updateBackgroundImage(QString)) );
}

void MainWindow::createMenuBar()
{
  // File Menu
  auto file_menu = menuBar()->addMenu( "&File" );

    // New map action
    auto* action = new QAction{ QIcon("resources/images/icons/new.png"), "New", this };
    file_menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(newMap()));

    // Save map action
    action = new QAction{ QIcon("resources/images/icons/save.png"), "Save", this };
    file_menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(saveMap()));

    // Open map action
    action = new QAction{ QIcon("resources/images/icons/open.png"), "Open", this };
    _shortcuts.emplace(Shortcut::OpenMap, QKeySequence("Ctrl+O"));
    action->setShortcut(_shortcuts[Shortcut::OpenMap]);
    file_menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(openMap()));

    // Quit action
    action = new QAction{ QIcon("resources/images/icons/quit.png"), "Quit", this };
    file_menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(close()));

  // Design Menu
  auto design_menu = menuBar()->addMenu( "&Design" );

    // Map background
    action = new QAction{ QIcon("resources/images/icons/map_background.png"), "Map background", this };
    _shortcuts.emplace(Shortcut::ChooseMapBackgroundImage, QKeySequence("Ctrl+M"));
    action->setShortcut(_shortcuts[Shortcut::ChooseMapBackgroundImage]);
    design_menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(showMapBackgroundDialog()));

  // Tools Menu
  auto tools_menu = menuBar()->addMenu( "&Tools" );

    // Map background
    action = new QAction{ QIcon("resources/images/icons/grid.png"), "Show/Hide Grid", this };
    _shortcuts.emplace(Shortcut::ToggleGridVisibility, QKeySequence("G"));
    action->setShortcut(_shortcuts[Shortcut::ToggleGridVisibility]);
    tools_menu->addAction(action);
    connect(action, SIGNAL(triggered()), _map_area, SLOT(toggleGridVisibility()));

  // About Menu
  auto about_menu = menuBar()->addMenu( "&About" );

    // Version
    action = new QAction{ QIcon("resources/images/icons/version.png"), "V0.1", this };
    about_menu->addAction(action);
}

void MainWindow::newMap()
{

}

void MainWindow::saveMap()
{
  using namespace rapidjson;

  if( _map_dir.isEmpty() )
    _map_dir = QFileDialog::getExistingDirectory(this);

  // Create JSON document
  Document map_json;
  map_json.SetObject();

  auto& map = map_json["map"];

  // Map name
  map.AddMember("name", _panel->mapInfo().name().toStdString().c_str(), map_json.GetAllocator());

  // Starting pos
  auto& start_pos = map["start_pos"];
  start_pos.AddMember("x", _panel->mapInfo().startPos().x(), map_json.GetAllocator());
  start_pos.AddMember("y", _panel->mapInfo().startPos().y(), map_json.GetAllocator());
  //map.AddMember("start_pos", start_pos);

  // Map size
  auto& map_size = map["size"];
  map_size.AddMember("w", _panel->mapInfo().nbrTiles().x(), map_json.GetAllocator());
  map_size.AddMember("h", _panel->mapInfo().nbrTiles().y(), map_json.GetAllocator());
  //map.AddMember("size", map_size);

  // Map name
  //map_json.AddMember("map", map);
}

void MainWindow::openMap()
{
  // User select a map file
  QString map_file_path = QFileDialog::getOpenFileName(this, "Choose a map file");

  // Try to read the file
  std::string file_content;
  if( !utils::files::read(map_file_path.toStdString(), file_content) )
  {
    QMessageBox::critical(this, "Open map error", "Can't read file");
    return;
  }

  // Read JSON
  using namespace rapidjson;
  rapidjson::Document document;
  document.Parse<0>(file_content.c_str());

  // Update UI elements
  _panel->openMap(document["map"]);
  _map_area->openMap(document["map"], map_file_path + ".png");
}

void MainWindow::showMapBackgroundDialog()
{
  _map_background->show();
  centerModal(_map_background);
}

void MainWindow::centerModal(QWidget* modal)
{
  if(!modal)
    return;

  int x = modal->width() < width() ? width() - modal->width() : modal->width() - width();
  int y = modal->height() < height() ? height() - modal->height() : modal->height() - height();
  modal->move( pos().x() + x / 2, pos().y() + y / 2 );
}
