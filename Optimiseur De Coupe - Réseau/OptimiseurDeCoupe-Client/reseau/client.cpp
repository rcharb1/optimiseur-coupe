#include "client.h"

Client::Client(QObject *parent) : QObject(parent), m_message(""), m_etat(0)
{
    m_fenetreDemande = new DemandeIpPort;
    connect(m_fenetreDemande, SIGNAL(demandeConnexion()), this, SLOT(connexion()));
    m_fenetreDemande->show();
}

int Client::sendMessage(QString message)
{
    if(! m_socket->isValid())
        return -1;
    qDebug() << "Client : Envoi du message au serveur";
    QByteArray Buffer;
    Buffer.append(message);

    if(m_socket->write(Buffer) == -1) {
        return -1;
    }
    qDebug() << "Client : message apparement bien envoyé";
    if(m_socket->flush())
        return 0;
    else
        return -1;
}

QString Client::message() const
{
    return m_message;
}

int Client::etat() const
{
    return m_etat;
}

void Client::readyRead()
{
    qDebug() << "Client : canReadLine()";
    while(! m_socket->canReadLine()) ;
    m_message = QString::fromUtf8(m_socket->readLine());
    qDebug() << "Client : message reçu : " << m_message;
}

void Client::connexion() {
    // connexion au serveur
    m_socket = new QTcpSocket(this);

    qDebug() << "Connexion...";
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
        QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        qDebug() << "Client : bien connecté !";
        emit bienConnecte();
    }
}
