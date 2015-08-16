/*
 * \file fenetreprincipale.h
 * \brief Header de la classe FenetrePrincipale
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include "formulaireSaisie.h"
#include "widgetresultats.h"
#include "./graphique/wigetgraphique.h"
#include "ongletinfo.h"
#include <QTcpSocket>
#include <QString>
#include <QMessageBox>
#include "reseau/protocoleodc_client.h"
#include "reseau/client.h"

/*
 * \class FenetrePrincipale fenetreprincipale.h
 * \brief Cette classe est la fenètre principale.
 * C'est elle qui gère les tabs, les widgets de formulaire, résultat et graphique.
 * C'est aussi elle qui lance le moteur et génère le texte des résultats.
 */

class FenetrePrincipale : public QWidget
{
    Q_OBJECT
public:
    // \brief Constructeur de la classe FenetrePrincipale
    explicit FenetrePrincipale(QWidget *parent = 0);

    // \brief Créé la représentation d'une liste de barres ou de tronçons
    // \return La chaîne de caractère à aficher
    QString listToStr(QVector<double> liste);

signals:

private:
    QTabWidget * m_tabs;
    FormulaireSaisie * m_formulaireSaisie;
    WidgetResultats * m_widgetResultats;
    WidgetGraphique * m_widgetGraphique;
    QTcpSocket * m_socket;
    Client * m_client;
public slots:
    /*
     * \brief Slot traitant le formulaire
     * C'est ce slot qui va vérifié si il y a une erreur (sauf celle du manque
     * de matière première qui est vérifiée par le moteur), lancé le moteur, généré
     * le texte à afficher dans l'onglet "Résultats" et envoyer les données nécessaires
     * pour la génération du graphique
     */
    void traiterFormulaire();

private slots:
    /*
     * \brief Signal lorsque le client est bien connecté au serveur
     */
    void bienConnecte();

    /*
     * \brief Signal lorsque le serveur s'est déconnecté.
     */
    void deconnexion();
};

#endif // FENETREPRINCIPALE_H
