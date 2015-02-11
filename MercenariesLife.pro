TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    graphics/drawables/map.cpp \
    graphics/drawables/drawable.cpp \
    utils/files/file.cpp \
    graphics/drawables/image.cpp \
    graphics/textures.cpp \
    models/character.cpp \
    models/player.cpp \
    graphics/drawables/map_character.cpp \
    utils/resources/game_config.cpp

LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lboost_filesystem -lboost_regex -lboost_system

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    graphics/drawables/map.hpp \
    graphics/drawables/drawable.hpp \
    utils/files/file.hpp \
    utils/resources/resource.hpp \
    graphics/drawables/image.hpp \
    graphics/textures.hpp \
    utils/position.hpp \
    models/character.hpp \
    models/player.hpp \
    graphics/drawables/map_character.hpp \
    utils/resources/game_config.hpp
