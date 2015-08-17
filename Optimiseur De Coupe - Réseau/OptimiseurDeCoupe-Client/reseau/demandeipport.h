#ifndef DEMANDEIPPORT_H
#define DEMANDEIPPORT_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QApplication>

class DemandeIpPort : public QWidget
{
    Q_OBJECT
public:
    explicit DemandeIpPort(QWidget *parent = 0);
    QString ip() const;
    int port() const;

private:
    QLineEdit * m_ip;
    QSpinBox * m_port;
    QPushButton * m_connexion;
signals:
    void demandeConnexion();
private slots:
    void boutonConnexion();
    void ipModifie(QString ip);
};

#endif // DEMANDEIPPORT_H
