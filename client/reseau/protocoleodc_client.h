/*
 * \file ProtocoleODC_client.h
 * \brief class ProtocoleODC_client Protocole de communication entre les clients et le serveur de l'Optimiseur de Coupe
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#ifndef PROTOCOLEODC_CLIENT_H
#define PROTOCOLEODC_CLIENT_H

#include <QString>
#include <QVector>
#include "saisies/saisie.h"
#include "combinaison.h"

/*
 * \class ProtocoleODC_client ProtocoleODC_client.h
 *
 * Classe permettant de créer le message à envoyer au serveur contenant les données
 * saisies par l'utilisateur dans le formulaire de saisie et de transformer la réponse
 * du serveur en données exploitables.
 * Dans le premier cas, la méthode statique createMessage suffit. Dans le second il faut
 * créer l'objet.
 */

class ProtocoleODC_client
{
public:
    /*
     * \brief Constructeur de la classe ProtocoleODC_client qui permet d'exploiter un message
     * \param type 1 pour une demande du client au serveur, 2 pour les résultats
     * \param message à convertir
     */
    ProtocoleODC_client(QString message);

    /*
     * \brief Créer le message contenant les données du formulaire de saisie pour le serveur
     * \param resultatsBarres Vecteur des saisies des barres avant la découpe
     * \param resultatsTron Vecteur des saisies des tronçons désirés
     * \param epaisseurLame Epaisseur de la lame en mm
     */
    static QString createMessage(QVector<Saisie *> resultatsBarres, QVector<Saisie *> resultatsTron, double epaisseurLame);

    /*
     * \brief Méthode d'accès à la liste des résultats
     * \return la liste des résultats
     */
    QVector<Combinaison *> resultats() const;

    /*
     * \brief Méthode d'accès au rendement total
     * \return le rendement total
     */
    double rendementTotal() const;

    /*
     * \brief Méthode d'accès aux tronçons restants
     * \return la liste des tronçons restants
     */
    QVector<double> tronconsRestants() const;

    /*
     * \brief Méthode d'accès aux barres restantes
     * \return la liste des barres restantes
     */
    QVector<double> barresRestantes() const;

    /*
     * \brief Méthode d'accès à l'état
     * \return 0 en cas d'erreur, 1 calculs trop grands, 2 réussi
     */
    int etat() const;

    QString erreur() const;

private:
    QVector<Combinaison *> m_listResultats;
    double m_rendementTotal;
    QVector<double> m_troncRestants;
    QVector<double> m_barresRestantes;
    int m_etat;
    QString m_erreur;
};

#endif // PROTOCOLEODC_CLIENT_H
