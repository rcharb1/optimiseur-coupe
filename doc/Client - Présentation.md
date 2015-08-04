Présentation du client
===

Actuellement, le dossier reseau contient 2 classes :
**ProtocoleODC_client** et **Combinaison**.

La dernière est une simple structure de données qui contient une Combinaison. Elle remplace la structure de données /moteur/combinaison.h de l'Optimiseur de Coupe original.

**ProtocoleODC_client** est la classe gère le protocole ODC. Elle permet :
1. De créer le message que le client doit envoyer au serveur via une méthode statique
2. D'analyser la réponse du serveur en convertissant la chaîne de caractère en variables exploitables (liste des combinaisons, rendement total etc...)

Le fichier **fenetrePrincipale.cpp** gère la fenêtre principale.
De la ligne 12 à la ligne 72, le programme demande à l'utilisatuer l'ip et le port. A partir de la ligne 163, le programme envoie une demande au serveur et affiche les résultats renvoyés.
