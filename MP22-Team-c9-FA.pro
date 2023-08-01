QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Source files
SOURCES += \
    src/model/worldmodel.cpp \
    src/model/xenemy.cpp \
    src/view/mainwindow.cpp \
    src/view/graphicalview.cpp \
    src/view/textview.cpp \
    src/controller/controller.cpp \
    src/pathfinder/astar.cpp \
    src/main.cpp \
    # main_test.cpp \
    tests/worldmodel_test.cpp 

# Header files
HEADERS += \
    src/model/worldmodel.h \
    src/model/xenemy.h \
    src/view/mainwindow.h \
    src/view/graphicalview.h \
    src/view/textview.h \
    src/view/view.h \
    src/view/image_widget.h \
    src/controller/controller.h \
    src/pathfinder/astar.h \
    include/world_global.h \
    include/world.h

# Forms
FORMS += \
    mainwindow.ui

# Resources
RESOURCES += \
    resources.qrc

# Add the include directories
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/src/model
INCLUDEPATH += $$PWD/src/view
INCLUDEPATH += $$PWD/src/controller
INCLUDEPATH += $$PWD/src/pathfinder
INCLUDEPATH += $$PWD/googletest/googletest/include

# Add the library directories
LIBS += -L$$PWD/lib
LIBS += -L$$PWD/googletest/build/lib

# Libraries to link
LIBS += -lworld 

# Link the world and Google Test libraries for all platforms
LIBS += -lgtest -lgtest_main

# Additional platform-specific configurations can be added here if necessary.

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Set the dependencies and include path
DEPENDPATH += $$PWD