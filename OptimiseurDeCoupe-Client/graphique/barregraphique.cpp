/*
 * \file barregraphique.cpp
 * \brief Source de la classe BarreGraphique
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#include "barregraphique.h"

BarreGraphique::BarreGraphique(Combinaison * combinaison, QWidget *parent) :QWidget(parent), m_combinaison(combinaison)
{
    /* On fait tout cela dans le constructeur et
     * des copies simples des membres de m_combinaison car
     * utiliser directement les méthodes d'accès dans paintEvent
     * cause une erreur de segmentation dont l'origine m'est inconnu.
     */
    setMinimumHeight(65);
    setMinimumWidth(500);
    m_liste = m_combinaison->troncons();
    m_barre = m_combinaison->barre();
}


// Dessine la découpe d'une barre
void BarreGraphique::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    // Affiche "Sur une barre de ...
    painter.drawText(QPoint(0,10), tr("Sur une barre de ") + ConvertUnit::toStrSimplifie(m_barre) + " :");

    // Calcul le nb de pixels dispos
    int longueur = 0, i,j, typeAffichage;
    double longueurUtilisee = 0;
    longueur = m_liste.length();
    longueur = 500 - ((longueur-1)*5); // 5 px d'espace entre les carrés

    // Calcul la longueur réellement utilisée
    for (i = 0; i < m_liste.length() ; i++)
        longueurUtilisee += m_liste[i];

    // Calcul la façon dont sera affiché le graphique
    // 1 : on essaye d'afficher les restes
    // 0 : on affiche juste les coupes à faire sans prendre en compte les restes
    // Ceci permet d'éviter les cas ou la découpe est trop petite pour afficher le label longueur
    if((longueur * (int) m_liste[0] / m_barre) < 45){
        typeAffichage = 0;
    }
    else
        typeAffichage = 1;

    // QPoints
    QPoint a(0,20), b;
    b.setY(55);

    QRect rec;

    // Affichage des rectangles
    for (j = 0; j < m_liste.length(); j++){
        if(typeAffichage == 1)
            i = (longueur * (int) m_liste[j]) / m_barre;
        else
            i = (longueur * (int) m_liste[j]) / (int) longueurUtilisee;
        b.setX(a.x() + i);
        rec.setTopLeft(a);
        rec.setBottomRight(b);
        painter.drawRect(rec);
        painter.drawText(rec, Qt::AlignCenter, ConvertUnit::toStrSimplifie(m_liste[j]));
        a.setX(b.x() + 5);
    }

    // Affichage des restes
    if(typeAffichage == 1 && longueurUtilisee < m_barre){
        i = (longueur * (int) (m_barre - longueurUtilisee) / m_barre);
        if(i > 55){
            painter.setPen(Qt::DashLine);
            b.setX(500);
            rec.setTopLeft(a);
            rec.setBottomRight(b);
            painter.drawRect(rec);
            painter.drawText(rec, Qt::AlignCenter, ConvertUnit::toStrSimplifie(m_barre-longueurUtilisee)+tr("\nrestants"));
        }
    }
}
