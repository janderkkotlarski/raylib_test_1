CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

# High warnings levels
# -Werror
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Weffc++

# Allow debug and release mode
CONFIG += debug_and_release

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
#  -lglfw3 -lopenal32

SOURCES += \
        cube_type.cpp \
        fractacube.cpp \
        main.cpp \
        misc_functions.cpp \
        vec_3_int.cpp

HEADERS += \
  cube_type.h \
  fractacube.h \
  misc_functions.h \
  vec_3_int.h
