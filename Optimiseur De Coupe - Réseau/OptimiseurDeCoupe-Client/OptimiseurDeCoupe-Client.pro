HEADERS += \
    saisies/groupesaisie.h \
    saisies/saisie.h \
    convertunit.h \
    fenetreprincipale.h \
    formulaireSaisie.h \
    widgetresultats.h \
    wigetgraphique.h \
    graphique/barregraphique.h \
    graphique/wigetgraphique.h \
    ongletinfo.h \
    reseau/protocoleodc_client.h \
    reseau/combinaison.h \
    reseau/client.h \
    reseau/demandeipport.h

SOURCES += \
    saisies/groupesaisie.cpp \
    saisies/saisie.cpp \
    convertunit.cpp \
    fenetreprincipale.cpp \
    formulaireSaisie.cpp \
    main.cpp \
    widgetresultats.cpp \
    graphique/barregraphique.cpp \
    graphique/wigetgraphique.cpp \
    ongletinfo.cpp \
    reseau/protocoleodc_client.cpp \
    reseau/combinaison.cpp \
    reseau/client.cpp \
    reseau/demandeipport.cpp

QT += widgets
QT += core
QT += network

TRANSLATIONS = optimiseurdecoupe_en.ts

RC_ICONS = mainIcon.ico
