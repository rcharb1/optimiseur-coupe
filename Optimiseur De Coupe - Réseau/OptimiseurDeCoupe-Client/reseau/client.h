#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QMessageBox>
#include <QApplication>
#include <QWidget>
#include "demandeipport.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    int sendMessage(QString message);
    QString message() const;
    int etat() const;
private:
    QTcpSocket * m_socket;
    QString m_message;
    DemandeIpPort * m_fenetreDemande;
    int m_etat;
signals:
    void bienConnecte();
public slots:
    void readyRead();
    void connexion();
};

#endif // CLIENT_H
