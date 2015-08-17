/* client.cpp
 * Optimiseur de Coupe
 * 2015 - Rebecca Charbit
 */

#include "client.h"

Client::Client(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(100); // peut lancer 100 fois le serveur
}

void Client::setSocket(qintptr descriptor)
{
    // créé la socket
    socket = new QTcpSocket(this);

    qDebug() << "Socket créée";

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(descriptor);

    qDebug() << " Client connecté : " << descriptor;
}


void Client::connected()
{
    qDebug() << "Client connecté !";
}

void Client::disconnected()
{
    qDebug() << "Client déconnecté";
}

void Client::readyRead()
{
    qDebug() << "Client ReadyRead ... ";

    while(! socket->canReadLine()) ;
    QString message(socket->readLine());
    qDebug() << "Le message reçu : " << message <<"\n";

    Task *mytask = new Task(message);
    mytask->setAutoDelete(true);
    
    connect(mytask, SIGNAL(Result(QString)), this, SLOT(TaskResult(QString)), Qt::QueuedConnection);

    qDebug() << "Starting a new task using a thread from the QThreadPool";
    
    QThreadPool::globalInstance()->start(mytask);   // lance Task::run()

}

void Client::TaskResult(QString message)
{
    QByteArray Buffer;
    Buffer.append(message);

    socket->write(Buffer);
    socket->flush();
}
