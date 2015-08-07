/*
 * \file ProtocoleODC_serveur.h
 * \brief class ProtocoleODC_serveur Protocole de communication entre les clients et le serveur de l'Optimiseur de Coupe
 * \author Rebecca Charbit 13409175
 * \date 2015
 */

#ifndef PROTOCOLEODC_SERVEUR_H
#define PROTOCOLEODC_SERVEUR_H

#include <QString>
#include <QVector>
#include "moteur/convert/convertunit.h"
#include "moteur/combinaison.h"
#include "moteur/MoteurCalculs.h"
#include "moteur/Paire.h"
#include "moteur/List.h"
#include <QDebug>

/*
 * \class ProtocoleODC_serveur ProtocoleODC_serveur.h
 *
 * Classe permettant de transformer les données envoyées par le client en données exploitables
 * et de créer le message à envoyer au client contenant les réponses
 * renvoyées par le programme (create_message).
 */

class ProtocoleODC_serveur
{
public:
    /*
     * \brief Constructeur de la classe ProtocoleODC_serveur qui permet d'exploiter un message
     * \param type 1 pour une demande du client au serveur, 2 pour les résultats
     * \param message à convertir
     */
    ProtocoleODC_serveur(QString message);

    /*
     * \brief Créer le message contenant les réponses pour le client
     * \param objet MoteurCalculs qui contient tous les résultats des calculs
     */
    static QString createMessage(MoteurCalculs results);

    /*
     * \brief Méthode d'accès à la liste des résultats
     * \return la liste des résultats
     */

private:
    MoteurCalculs * m_results;
};

#endif // PROTOCOLEODC_SERVEUR_H
