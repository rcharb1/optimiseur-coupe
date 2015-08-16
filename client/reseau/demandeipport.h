/*
 * \file saisie.h
 * \brief Header de la classe Saisie
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#ifndef DEMANDEIPPORT_H
#define DEMANDEIPPORT_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QHostInfo>
#include <QNetworkInterface>

/*
 * \class DemandeIpPort demandeipport.h
 * \brief Classe affichant la fenêtre demandant l'ip et le port
 */
class DemandeIpPort : public QWidget
{
    Q_OBJECT
public:
    /*
     * \brief Constructeur de la classe
     */
    explicit DemandeIpPort(QWidget *parent = 0);

    /*
     * \brief Méthode d'accès à l'ip
     * \return l'ip
     */
    QString ip() const;

    /*
     * \brief Méthode d'accès au port
     * \return le port
     */
    int port() const;

private:
    QComboBox * m_ip;
    QSpinBox * m_port;
    QPushButton * m_connexion;
signals:
    /*
     * \brief Signal pour lancer la connexion lorsque l'utilisateur clique sur "Connexion".
     */
    void demandeConnexion();

private slots:
    /*
     * \brief Slot lancé lorsque le bouton "Connexion" est appuyé.
     *      Ferme la fenêtre et lance le signal DemandeIpPort::demandeConnexion().
     */
    void boutonConnexion();

    /*
     * \brief Slop lancé lorsque le champ ip est modifié.
     *      Permet de désactiver le bouton "Connexion" lorsque ce champ est vide.
     */
    void ipModifie(QString ip);
};

#endif // DEMANDEIPPORT_H
