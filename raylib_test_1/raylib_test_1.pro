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

LIBS += -LC:/raylib/MinGW/bin
LIBS += -LC:\raylib\src\external\glfw
LIBS += -Iexternal -lraylib -lopengl32 -lgdi32 -lwinmm
# -lglfw3 -lopenal32

SOURCES += \
        main.cpp
