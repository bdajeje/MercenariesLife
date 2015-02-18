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
    graphics/drawables/animation.cpp \
    graphics/drawables/user_interface.cpp \
    graphics/fonts.cpp \
    models/pnj.cpp \
    events/events.cpp \
    models/conversation.cpp \
    events/keyboard_listener.cpp

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
    utils/direction.hpp \
    graphics/drawables/user_interface.hpp \
    graphics/fonts.hpp \
    models/pnj.hpp \
    events/events.hpp \
    models/conversation.hpp \
    events/keyboard_listener.hpp
