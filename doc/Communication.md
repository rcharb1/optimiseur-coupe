Optimiseur de coupe - Protocole pour le réseau
===

Toutes les valeurs sont en mm.

L'utilisation de plusieurs séparateurs (`!|;/`) permet d'utiliser plusieurs fois la fonction QString::split() plus facilement.

## Envoi du formulaire de saisie
String de type :

`"ODC-START!taille;nb|taille;nb|...!taille;nb|taille;nb|...!epaisseurLame!ODC-END"`

Le serveur doit vérifier que la QStringList renvoyée par `message.split('!')` contient bien 5 éléments, qui sont:
1. ODC-START
2. Les barres avant la découpe
3. Les tronçons désirés
4. L'épaisseur de la lame
5. ODC-END.

De plus, le serveur doit vérifier que le premier élément est `ODC-START` et le dernier `ODC-END`.

Sans avoir vérifier ces trois conditions (5 éléments, présence de ODC-START, présence de ODC-END), le serveur ne doit pas traiter le message.

## Envoi des résultats

`"ODC-START!barre/tronçon;tronçon;.../rendement|barre/tronçon;tronçon;.../rendement|barre/tronçon;tronçon;.../rendement!rendementTotal!barreRest;barreRest;...!tronRest;tronRest;...!ODC-END"`

Le client doit vérifier que la QStringList renvoyée par `message.split('!')` contient bien 6 éléments, qui sont:
1. ODC-START
2. Les combinaisons
3. Le rendement total
4. Les barres restantes
5. Les tronçons restants
6. ODC-END.

De plus, le client doit vérifier que le premier élément est `ODC-START` et le dernier `ODC-END`.

Sans avoir vérifier ces trois conditions (6 éléments, présence de ODC-START, présence de ODC-END), le client ne doit pas traiter le message.

## Fonctions de Qt à utiliser
* `QStringList QString::split()` : permet de découper un string en une liste de string
* `double QString::toDouble()` : convertit un string contenant un nombre en double.
* `QString::number()` : convertit un nombre en QString
