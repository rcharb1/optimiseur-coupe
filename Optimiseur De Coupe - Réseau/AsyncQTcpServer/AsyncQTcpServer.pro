QT       += core
QT       += network
QT       += widgets


TARGET = OptimiseurDeCoupe_Serveur
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myserver.cpp \
    myclient.cpp \
    mytask.cpp \
    moteur/Combinaison.cpp \
    moteur/List.cpp \
    moteur/MoteurCalculs.cpp \
    moteur/Paire.cpp \
    reseau/protocoleodc_serveur.cpp

HEADERS += \
    myserver.h \
    myclient.h \
    mytask.h \
    moteur/Combinaison.h \
    moteur/List.h \
    moteur/MoteurCalculs.h \
    moteur/Paire.h \
    reseau/protocoleodc_serveur.h
