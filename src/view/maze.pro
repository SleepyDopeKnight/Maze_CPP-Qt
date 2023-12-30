QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../main.cc \
    maze_view.cc \
    ../model/maze_facade.cc \
    ../model/maze_generator/maze_generator.cc \
    ../model/maze_solver/maze_solver.cc \
    ../controllers/maze_controllers.cc \
    ./draw/draw_widget.cc \
    ./control/control_widget.cc \

HEADERS += \
    ../model/maze_facade.h \
    ../model/maze_generator/maze_generator.h \
    ../model/maze_solver/maze_solver.h \
    maze_view.h \
    ../controllers/maze_controllers.h \
    ./draw/draw_widget.h \
    ./control/control_widget.h \

FORMS += \
    maze_view.ui \
    ./control/control_widget.ui \
    ./draw/draw_widget.ui \

ICON = $${PWD}/maze.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
