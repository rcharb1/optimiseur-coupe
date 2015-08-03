Optimiseur de coupe - Protocole pour le réseau
===

Toutes les valeurs sont en mm.

L'utilisation de plusieurs séparateurs (`!|;/`) permet d'utiliser plusieurs fois la fonction QString::split() plus facilement.

## Envoi du formulaire de saisie
String de type :

`"ODC-START!taille;nb|taille;nb|etc!taille;nb|taille;nb|etc!epaisseurLame!ODC-END"`

## Envoi des résultats

`"ODC-START!barre/tronçon;tronçon;...|barre/tronçon;tronçon;...|barre/tronçon;tronçon;...!rendementTotal!barreRest;barreRest;...!tronRest;tronRest;...!ODC-END"`

## Fonctions de Qt à utiliser
* `QStringList QString::split(const QString & sep;SplitBehavior behavior = KeepEmptyParts;Qt::CaseSensitivity cs = Qt::CaseSensitive) const` : permet de découper un string en une liste de string
* `double QString::toDouble(bool * ok = 0) const` : convertit un string contenant un nombre en double.
