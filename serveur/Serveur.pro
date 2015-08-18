HEADERS += \
    client.h \
    serveur.h \
    task.h \
    reseau/protocoleodc_serveur.h \
    moteur/Combinaison.h \
    moteur/List.h \
    moteur/MoteurCalculs.h \
    moteur/Paire.h

SOURCES += \
    client.cpp \
    main.cpp \
    serveur.cpp \
    task.cpp \
    reseau/protocoleodc_serveur.cpp \
    moteur/Combinaison.cpp \
    moteur/List.cpp \
    moteur/MoteurCalculs.cpp \
    moteur/Paire.cpp

QT += widgets
QT += core
QT += network

TRANSLATIONS = optimiseurdecoupe_en.ts

RC_ICONS = mainIcon.ico
