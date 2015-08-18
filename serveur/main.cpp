/* main.cpp
 * Optimiseur de Coupe
 * 2015 - Rebecca Charbit
 */

#include <QApplication>
#include <QTranslator>
#include "serveur.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    QFont police("Ubuntu", 10);
    police.setStyleHint(QFont::SansSerif);
    app.setFont(police);

    // Chargement de la traduction
    QString locale = QLocale::system().name().section('_', 0, 0);
    //locale = "en";
    QTranslator translator;
    translator.load("optimiseurdecoupe_"+locale);
    app.installTranslator(&translator);

    Serveur leServeur;
    leServeur.lancement();

    return app.exec();
}
