/*
 * \file saisie.h
 * \brief Header de la classe Saisie
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QMessageBox>
#include <QApplication>
/*
 * \file saisie.h
 * \brief Header de la classe Saisie
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#include <QWidget>
#include "demandeipport.h"


/*
 * \class Client client.h
 * \brief Gère la connexion avec le serveur,
 *      de la création de la socket à la fenêtre demandant l'ip et le port.
 */
class Client : public QObject
{
    Q_OBJECT
public:
    /*
     * \brief Constructeur du client qui lance la fenêtre demandant l'ip et le port.
     */
    explicit Client(QObject *parent = 0);

    /*
     * \brief Fonction qui envoie une requête au serveur
     * \param message le message à envoyer au serveur
     * \return 0 si tout s'est bien passé,
     *      -1 en cas d'erreur lors de l'envoie du message
     *      et -2 en cas d'erreur lors de la réception des résultats
     */
    int sendMessage(QString message);

    /*
     * \brief Méthode d'accès aux résultats
     * \return Les résultats du serveur
     */
    QString message() const;

private:
    QTcpSocket * m_socket;
    QString m_message;
    DemandeIpPort * m_fenetreDemande;
signals:
    /*
     * \brief Signal en cas de connexion. Nécessaire pour activer la fenêtre principale
     */
    void bienConnecte();

    /*
     * \brief Signal pour indiquer la déconnexion du serveur.
     */
    void signalDeconnexion();
public slots:
    /*
     * \brief Slot permettant la connexion du client au serveur.
     */
    void connexion();

    /*
     * \brief Slot permettant d'émettre le signal Client::signalDeconnexion()
     */
    void deconnextion();
};

#endif // CLIENT_H
