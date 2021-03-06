Optimiseur de coupe - Protocole ODC pour le réseau
===


## Envoi du formulaire de saisie
String de type :

`"ODC-START!taille;nb|taille;nb|...!taille;nb|taille;nb|...!epaisseurLame!ODC-END\n"`

Le serveur doit vérifier que la QStringList renvoyée par `message.split('!')` contient bien 5 éléments, qui sont:
1. ODC-START
2. Les barres avant la découpe
3. Les tronçons désirés
4. L'épaisseur de la lame
5. ODC-END\n.

De plus, le serveur doit vérifier que le premier élément est `ODC-START` et le dernier `ODC-END\n`.

Sans avoir vérifié ces trois conditions (5 éléments, présence de `ODC-START`, présence de `ODC-END\n`), le serveur ne doit pas traiter le message.

## Envoi des résultats

`"ODC-START!barre/tronçon;tronçon;.../rendement|barre/tronçon;tronçon;.../rendement|barre/tronçon;tronçon;.../rendement!rendementTotal!barreRest;barreRest;...!tronRest;tronRest;...!ODC-END\n"`

Si les calculs demandés sont trop grands, il faut envoyer ce message :

`"ODC-START!STOP-CALCULS!ODC-END\n"`

Sauf en cas de calculs trop grands, le client doit vérifier que la QStringList renvoyée par `message.split('!')` contient bien 6 éléments, qui sont:
1. ODC-START
2. Les combinaisons
3. Le rendement total
4. Les barres restantes
5. Les tronçons restants
6. ODC-END\n.

De plus, le client doit vérifier que le premier élément est `ODC-START` et le dernier `ODC-END\n`.

Sans avoir vérifié ces trois conditions (6 éléments, présence de `ODC-START`, présence de `ODC-END\n`), le client ne doit pas traiter le message.

## Informations diverses

Toutes les valeurs sont en mm.

L'utilisation de plusieurs séparateurs (`!|;/`) permet d'utiliser plusieurs fois la fonction QString::split() plus facilement.

Terminer les messages par un retour à la ligne permet d'utiliser les fonctions QAbstractSocket::readLine() et QAbstractSocket::canReadLine() de Qt.
