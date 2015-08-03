Optimiseur de coupe - Protocole pour le réseau
===

## Envoi du formulaire de saisie
String de type :

`"ODC-START;[[taille;nb];[taille;nb]; ...];[[taille;nb];[taille;nb]; ...];epaisseurLame;ODC-END"`

Avec :
* ODC-START : l'annonce du début du message
* ODC-END : l'annonce de la fin du message
* taille  : la taille en mm de la barre ou du tronçon
* nb : le nombre de barres ou de barres de cette taille
* epaisseurLame : l'épaisseur de la lame en mm

## Envoi des résultats

`"ODC-START;[[barre;[tronçon;tronçon; ...];rendement];[barre;[tronçon;tronçon; ...];rendement] ...];rendementTotal;[tronRest;tronRest; ...];[barreRest;barreRest; ...];ODC-END"`

## Fonctions de Qt à utiliser
* `QStringList QString::split(const QString & sep;SplitBehavior behavior = KeepEmptyParts;Qt::CaseSensitivity cs = Qt::CaseSensitive) const` : permet de découper un string en une liste de string
* `double QString::toDouble(bool * ok = 0) const` : convertit un string contenant un nombre en double.
