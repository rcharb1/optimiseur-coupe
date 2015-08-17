/* protocoleodc_serveur.h
 * Optimiseur de Coupe
 * 2015 - Rebecca Charbit
 */

#ifndef PROTOCOLEODC_SERVEUR_H
#define PROTOCOLEODC_SERVEUR_H

#include <QString>
#include <QVector>
#include "../moteur/Combinaison.h"
#include <QDebug>
#include <list>
#include "../moteur/List.h"
#include "../moteur/Paire.h"

/*
 * \class ProtocoleODC_serveur ProtocoleODC_serveur.h
 *
 * Classe permettant de créer le message à envoyer au client contenant les résultats
 * du moteur et de transformer la réponse du client en données exploitables.
 * Dans le premier cas, la méthode statique createMessage suffit.
 * Dans le second il faut créer l'objet.
 */

class ProtocoleODC_serveur
{
public:
    /*
     * \brief Constructeur de la classe ProtocoleODC_serveur qui permet d'exploiter un message reçu
     * \param message à convertir
     * (Il faut utiliser les méthodes d'accès pour accéder aux résultats)
     */
    ProtocoleODC_serveur(QString message);

    static QString sendCalculsTropGrands() ;

    /*
     * \brief Créer le message contenant les données du formulaire de saisie pour le client
     * \param pointResultatFinal Liste des combinaisons finales
     * \param rendementTotal Rendement total
     * \param barres Barres restantes
     * \param troncons Tronçons restants
     * \return Le QString du message à envoyer
     */
    static QString createMessage(std::list<Combinaison> * pointResultatFinal, double rendementTotal, List * barres, List * troncons);

    /*
     * \brief Accès aux barres disponibles
     * \return Un vecteur de double contenant la longueur des barres disponibles
     */
    QVector<double> getBarresVecteur() const;

    /*
     * \brief Accès aux tronçons désirés
     * \return Un vecteur de double contenant la longueur des tronçons désirés
    */
    QVector<double> getTronconsVecteur() const;

    /*
     * \brief Accès à l'épaisseur de la lame
     * \return L'épaisseur de la lame
     */
    double getEpaisseurLame() const;

    /*
     * \brief Accès à l'état
     * \return 1 si le traitement du message s'est bien passé, 0 en cas d'erreur.
     */
    int getEtat() const;

private:
    QVector<double> m_barresVecteur;
    QVector<double> m_tronconsVecteur;
    double m_epaisseurLame;
    int m_etat;
};

#endif // PROTOCOLEODC_SERVEUR_H
