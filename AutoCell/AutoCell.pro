QT += widgets

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11


HEADERS += \
    automateexception.h \
    cabuilder.h \
    cell.h \
    cellularautomata.h \
    etat.h \
    fenetre1d.h \
    fenetre2d.h \
    fenetreconfig.h \
    fichier.h \
    generateuretat.h \
    mainwindow.h \
    sauvegarde.h \
    transitionrule.h \
    voisinage.h \
    fenetresimulation.h

SOURCES += \
    cell.cpp \
    cellularautomata.cpp \
    etat.cpp \
    fenetre1d.cpp \
    fenetre2d.cpp \
    fenetreconfig.cpp \
    fichier.cpp \
    generateuretat.cpp \
    main.cpp \
    mainwindow.cpp \
    sauvegarde.cpp \
    transitionrule.cpp \
    voisinage.cpp \
    fenetresimulation.cpp
