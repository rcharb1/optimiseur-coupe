// myserver.h

#ifndef MYSERVER_H
#define MYSERVER_H

#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "myclient.h"
#include <QDebug>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void startServer();
protected:
    void incomingConnection(qintptr socketDescriptor);

signals:
    void quitter();
public slots:

};

#endif // MYSERVER_H
