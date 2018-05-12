QT += widgets

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11
SOURCES += \
    main.cpp \
    cell.cpp \
    generateuretat.cpp \
    etat.cpp \
    voisinage.cpp

HEADERS += \
    cell.h \
    generateuretat.h \
    etat.h \
    voisinage.h
