TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    graphics/drawables/map.cpp \
    utils/files/file.cpp \
    graphics/textures.cpp \
    models/character.cpp \
    models/player.cpp \
    graphics/drawables/map_character.cpp \
    utils/resources/game_config.cpp \
    utils/conversions.cpp \
    graphics/drawables/animation.cpp

LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lboost_filesystem -lboost_regex -lboost_system

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    graphics/drawables/map.hpp \
    utils/files/file.hpp \
    utils/resources/resource.hpp \
    graphics/textures.hpp \
    utils/position.hpp \
    models/character.hpp \
    models/player.hpp \
    graphics/drawables/map_character.hpp \
    utils/resources/game_config.hpp \
    utils/conversions.hpp \
    graphics/drawables/animation.hpp \
    utils/direction.hpp
