// myserver.cpp

#include "myserver.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
}

void MyServer::startServer()
{
    QObject::connect(this, SIGNAL(quitter()), qApp, SLOT(quit()));
    qDebug() << "Serveur lancé";
    QString text;
    bool ok;
    QWidget * fenetre = new QWidget();
    int port = QInputDialog::getInt(fenetre, tr("Optimiseur de Coupe - Serveur"),
                                    tr("Numéro de port à utiliser"),1050, 1024, 65536, 1, &ok);
    if (!ok){
        emit quitter();   // quitte l'application si 'Cancel' a été cliqué
    }
    else {
        if(listen(QHostAddress::Any, port)) {
            text = tr("Le serveur a été démarré sur le port") + " <strong>";
            text += QString::number(serverPort());
            text += "</strong>.<br />" + tr("Des clients peuvent maintenant se connecter.");
        }
        else {
            text = tr("Le serveur n'a pas pu être démarré. Raison :") + "<br />" + errorString();
        }

        // Titre de la fenêtre
        fenetre->setWindowTitle(tr("Optimiseur de coupe"));
        fenetre->setWindowIcon(QIcon("mainIcon.ico"));

        // layout
        QVBoxLayout * mainLayout = new QVBoxLayout;

        // message
        QLabel * message = new QLabel(text);
        mainLayout->addWidget(message);

        // bouton quitter
        QPushButton * quitter = new QPushButton(tr("Quitter"));
        mainLayout->addWidget(quitter);
        QObject::connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));

        fenetre->setLayout(mainLayout);

        fenetre->show();
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor) {
    // At the incoming connection, make a client
    // and set the socket
    qDebug() << "Nouvelle Connexion";
    MyClient *client = new MyClient(this);
    client->setSocket(socketDescriptor);
}
