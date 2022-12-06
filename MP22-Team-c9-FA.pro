QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    astar.cpp \
    main.cpp \
    mainwindow.cpp \


HEADERS += \
    ImageWidget.h \
    astar.h \
    lib/world.h \
    lib/world_global.h \
    mainwindow.h \
    view.h \
    world.h \
    world_global.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lworld
else:unix: LIBS += -L$$PWD/lib/ -lworld

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

RESOURCES += \
    resources.qrc
