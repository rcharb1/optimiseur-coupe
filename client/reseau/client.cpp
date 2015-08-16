/*
 * \file saisie.h
 * \brief Header de la classe Saisie
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#include "client.h"

Client::Client(QObject *parent) : QObject(parent), m_message("")
{
    m_fenetreDemande = new DemandeIpPort;
    connect(m_fenetreDemande, SIGNAL(demandeConnexion()), this, SLOT(connexion()));
    m_fenetreDemande->show();
}

void Client::connexion() {
    // connexion au serveur
    m_socket = new QTcpSocket(this);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(deconnextion()));

    //connexion
    m_socket->connectToHost(m_fenetreDemande->ip(), m_fenetreDemande->port());

    // attend la connextion
    if(! m_socket->waitForConnected()) {
        // Affichage du message d'errur
        QMessageBox erreurMessageBox;
        switch (m_socket->error()) {
            case QAbstractSocket::HostNotFoundError:
                erreurMessageBox.setText(tr("Erreur : le serveur n'a pas pu être trouvé."));
                erreurMessageBox.setInformativeText(tr("Vérifiez l'adresse IP et le port."));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            erreurMessageBox.setText(tr("Erreur : le serveur a refusé la connexion."));
            erreurMessageBox.setInformativeText(tr("Vérifiez si le serveur a bien été lancé. Vérifiez aussi l'adresse IP et le port."));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            erreurMessageBox.setText(tr("Erreur : le serveur a coupé la connexion."));
            erreurMessageBox.setInformativeText(tr("Veuillez réessayer plus tard."));
            break;
        default:
            erreurMessageBox.setText(tr("Erreur : ") + m_socket->errorString());
            break;
        }
        erreurMessageBox.setIcon(QMessageBox::Critical);
        erreurMessageBox.setWindowTitle(tr("Erreur - Connexion au serveur"));
        erreurMessageBox.setStandardButtons(QMessageBox::Close);
        if (erreurMessageBox.exec() == QMessageBox::Close) {
            qApp->quit();
        }
     }
    else {
        emit bienConnecte();
    }
}

void Client::deconnextion()
{
    emit signalDeconnexion();
}

int Client::sendMessage(QString message)
{
    if(! m_socket->isValid())
        return -1;

    QByteArray Buffer;
    Buffer.append(message);

    if(m_socket->write(Buffer) == -1)
        return -1;

    if(! m_socket->flush())
        return -1;

    if(m_socket->waitForReadyRead() == false)
        return -2;

    while(! m_socket->canReadLine()) ;
    m_message = QString::fromUtf8(m_socket->readLine());

    return 0;
}

QString Client::message() const
{
    return m_message;
}
