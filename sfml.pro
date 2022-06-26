TEMPLATE = app
CONFIG += console c++23
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../home/vasabi/sfml_src/SFML/yeah/lib/release/ -lsfml-graphics -lsfml-window -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../home/vasabi/sfml_src/SFML/yeah/lib/debug/ -lsfml-graphics -lsfml-window -lsfml-system
else:unix: LIBS += -L$$PWD/../../../../../../../home/vasabi/sfml_src/SFML/yeah/lib/ -lsfml-graphics -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/../../../../../../../home/vasabi/sfml_src/SFML/yeah/
DEPENDPATH += $$PWD/../../../../../../../home/vasabi/sfml_src/SFML/yeah/
INCLUDEPATH += $$PWD/../../../../../../../home/vasabi/sfml_src/SFML/yeah/
DEPENDPATH += /run/media/vasabi/DATA/linus/gt_projects/sfml/

HEADERS += \
    vector_utils.h
