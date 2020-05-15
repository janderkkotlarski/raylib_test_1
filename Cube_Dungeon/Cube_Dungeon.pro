CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

# High warnings levels
# -Werror
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Weffc++
QMAKE_CXXFLAGS += -static-libgcc -static-libstdc++

# Allow debug and release mode
CONFIG += debug_and_release

# CONFIG += staticlib

# In release mode, turn on profiling
CONFIG(release, debug|release) {

  DEFINES += NDEBUG

  # gprof
  QMAKE_CXXFLAGS += -pg
  QMAKE_LFLAGS += -pg
}

INCLUDEPATH += C:/raylib/raylib/src
INCLUDEPATH += C:/raylib/raylib

LIBS += -LC:/raylib/MinGW/bin
LIBS += -LC:/raylib/src/externa/glfw
LIBS += -LC:/raylib/raylib
LIBS += -Iexternal -lraylib -lopengl32 -lgdi32 -lwinmm
LIBS += -static -lpthread
#  -lglfw3 -lopenal32

SOURCES += \
        action.cpp \
        cube_type.cpp \
        dungeon_loop.cpp \
        dungeon_maze.cpp \
        fractacube.cpp \
        keybindings.cpp \
        main.cpp \
        misc_functions.cpp \
        raylib_functions.cpp \
        synchrogear.cpp \
        vec_3_int.cpp

HEADERS += \
  action.h \
  cube_type.h \
  dungeon_loop.h \
  dungeon_maze.h \
  fractacube.h \
  keybindings.h \
  misc_functions.h \
  raylib_functions.h \
  synchrogear.h \
  vec_3_int.h
