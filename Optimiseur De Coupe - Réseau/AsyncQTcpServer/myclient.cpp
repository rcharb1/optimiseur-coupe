// myclient.cpp

#include "myclient.h"

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(5);
}

void MyClient::setSocket(qintptr descriptor)
{
    // make a new socket
    socket = new QTcpSocket(this);

    qDebug() << "A new socket created!";

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(descriptor);

    qDebug() << " Client connected at " << descriptor;
}


// asynchronous - runs separately from the thread we created
void MyClient::connected()
{
    qDebug() << "Client connected event";
}

// asynchronous
void MyClient::disconnected()
{
    qDebug() << "Client disconnected";
}

// Our main thread of execution
// This happening via main thread
// Our code running in our current thread not in another QThread
// That's why we're getting the thread from the pool

void MyClient::readyRead()
{
    qDebug() << "Client ReadyRead ... ";

    while(! socket->canReadLine()) ;
    QString message(socket->readLine());
    qDebug() << "Le message reçu : " << message <<"\n";

    // Time consumer
    MyTask *mytask = new MyTask(message);
    mytask->setAutoDelete(true);
    
    // using queued connection
    connect(mytask, SIGNAL(Result(QString)), this, SLOT(TaskResult(QString)), Qt::QueuedConnection);

    qDebug() << "Starting a new task using a thread from the QThreadPool";
    
    // QThreadPool::globalInstance() returns global QThreadPool instance
    QThreadPool::globalInstance()->start(mytask);

}

// After a task performed a time consuming task,
// we grab the result here, and send it to client
void MyClient::TaskResult(QString message)
{
    QByteArray Buffer;
    Buffer.append(message);

    socket->write(Buffer);
    socket->flush();
}
